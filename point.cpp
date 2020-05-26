#include "point.h"
#include <iostream>


Point::Point(){
// Default constructor with no arguments. Point initialized at origin.
    coordinates[0] = 0;
    coordinates[1] = 0;
    coordinates[2] = 0;
}

Point::Point(double *X)
// Initializes a point from a pointer of coordinates
{
    for(int i=0; i<3; i++){
        try{
            coordinates[i] = X[i];
        }
        catch (...) {
            coordinates[i] = 0.0;
        }
    }
}

Point::Point(double x, double y=0, double z=0)
// Initializes a point from a list of doubles
{
    coordinates[0] = x;
    coordinates[1] = y;
    coordinates[2] = z;
}
