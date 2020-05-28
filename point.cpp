#include "point.h"
#include <iostream>


Point::Point(){
// Default constructor with no arguments. Point initialized at origin.
    coordinates[0] = 0;
    coordinates[1] = 0;
}

Point::Point(double *X)
// Initializes a point from a pointer of coordinates. Invalid values are 0.00
{
    coordinates[0] = X[0];
    coordinates[1] = X[1];
}

Point::Point(double x, double y=0)
// Initializes a point from a list of doubles
{
    coordinates[0] = x;
    coordinates[1] = y;
}
