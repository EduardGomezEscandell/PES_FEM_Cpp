#ifndef POINT_H
#define POINT_H

#include <iostream>


class Point
{
public:
    double coordinates[2];

    Point();
    Point(double *X);
    Point(double x, double y);
};

#endif // POINT_H
