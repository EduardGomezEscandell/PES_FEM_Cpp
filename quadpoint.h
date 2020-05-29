#ifndef QUADPOINT_H
#define QUADPOINT_H

#include "point.h"
#include "dependencies/Eigen/Dense"

class QuadPoint: public Point
{
public:
    double w;
    Eigen::MatrixXd N;
    Eigen::MatrixXd gradN;

    QuadPoint();
    QuadPoint(double weight, double *X);
    QuadPoint(double weight, double x, double y);
};

#endif // QUADPOINT_H
