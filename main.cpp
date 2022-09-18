#include <iostream>
#include <cmath>
using namespace std;

void shift(double vec[2], double x, double y){ //function to add (x,y) to the coordinates of vec.
    vec[0] += x;
    vec[1] += y;
}

// p = point 1, q = point 2, c = center of circle, r = radius, v = 1 indicates line is vertical, 0 indicates opposite
void intCalc (double p[2], double q[2], double c[2], double r, int v) {  
    shift(p, -c[0], -c[1]);    // By initially shifting the origin to the center of the circle, we avoid
    shift(q, -c[0], -c[1]);    // difficult calculation.
    double m = (p[1] - q[1]) / (p[0] - q[0]); // slope of line
    double b = p[1] - m * p[0]; // y-intercept of line
    double disc = sqrt(pow(m * b, 2) - (1 + pow(m,2)) * (pow(b,2) - pow(r,2))); // Discriminant of intersection equation based on geometry

    if (disc < 0) { 
        cout << "Intersection(s): none";
        exit;
    }

    double i1[2];
    double i2[2];

    if (v == 0){ // Straight forward calculation of intersection when line is not vertical
        i1[0] = (-m * b + disc) / (1 + pow(m, 2));
        i2[0] = (-m * b - disc) / (1 + pow(m, 2));
        i1[1] = m * i1[0] + b;
        i2[1] = m * i2[0] + b;
    } else {    // Calculates intersection, but also reverts coordinates back to x,y from y,x
        double x = p[0];
        double y = q[0];
        double z = c[0];
        p[0] = p[1];
        q[0] = q[1];
        c[0] = c[1];
        p[1] = x;
        q[1] = y;
        c[1] = z; 
        i1[1] = (-m * b + disc) / (1 + pow(m, 2));
        i2[1] = (-m * b - disc) / (1 + pow(m, 2));
        i1[0] = m * i1[0] + b;
        i2[0] = m * i2[0] + b;
    }

    shift(i1, c[0], c[1]); // shifts points back to original position
    shift(i2, c[0], c[1]);
    shift(p, c[0], c[1]);
    shift(q, c[0], c[1]);

    cout << "Intersection(s): ";

    double lowerX;
    double lowerY;
    double higherX;
    double higherY; 

    if (p[0] > q[0]){    // finds relative position of points using x coordinates
        higherX = p[0];
        lowerX = q[0]; 
    } else {
        higherX = q[0];
        lowerX = p[0];
    }

    if (p[1] > q[1]){    // same as above but using y coordintes
        higherY = p[1];
        lowerY = q[1]; 
    } else {
        higherY = q[1];
        lowerY = p[1];
    }
    
    if (v == 0){                                              // Checks if intersection points are between start and end points.
        if (i1[0] >= lowerX && i1[0] <= higherX)              // This is done using y coordinates for vertical lines and x coordinates 
            cout << "(" << i1[0] << "," << i1[1] << ")";      // for horizontal and diagonal lines. 
        if (i2[0] >= lowerX && i2[0] <= higherX)
            cout << "," << "(" << i2[0] << "," << i2[1] << ")";
    } else {
        if (i1[1] >= lowerY && i1[1] <= higherY) 
            cout << "(" << i1[0] << "," << i1[1] << ")";
        if (i2[1] >= lowerY && i2[1] <= higherY)
            cout << "," << "(" << i2[0] << "," << i2[1] << ")";
    }
}

// p = point 1, q = point 2, c = center of circle, r = radius
void intersect(double p[2], double q[2], double c[2], double r){
    if (p[0] == q[0]){
        double x = p[0]; // To avoid undefined slope, the calculation for a vertical line
        double y = q[0]; // is calculated with reversed x,y coordinate.
        double z = c[0];
        p[0] = p[1];
        q[0] = q[1];
        c[0] = c[1];
        p[1] = x;
        q[1] = y;
        c[1] = z; 
        intCalc (p, q, c, r, 1); 
    } else {
        intCalc (p, q, c, r, 0); 
    }
}


int main() {
    double tp1[] = {5,1};
    double tp2[] = {0,1};
    double tc1[] = {0,0};
    intersect(tp1, tp2, tc1, 1); // case: one intercept
    cout << "\n";
    double tp3[] = {4,-8};         
    double tp4[] = {4,-17};
    double tc2[] = {7,-12};
    intersect(tp3, tp4, tc2, 5); // case: vertical line
    cout << "\n";
    double tp5[] = {2,10};         
    double tp6[] = {0,3};
    double tc3[] = {4,5};
    intersect(tp5, tp6, tc3, 5); // case: one point on line but not between points
    cout << "\n";
    double tp7[] = {2,10};         
    double tp8[] = {-1,-0.5};
    double tc4[] = {4,5};
    intersect(tp7, tp8, tc4, 5); // case: same as above but both intersections between points

    return 0;
}