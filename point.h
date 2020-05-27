#ifndef POINT_H
#define POINT_H


class Point
{
public:
    double coordinates[3];

    Point();
    Point(double *X);
    Point(double x, double y);
};

#endif // POINT_H
