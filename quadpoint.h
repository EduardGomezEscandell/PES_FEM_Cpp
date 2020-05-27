#ifndef QUADPOINT_H
#define QUADPOINT_H
#include "point.h"

#ifndef EIGEN_DENSE_H
    #define EIGEN_DENSE_H
    #include "Eigen/Dense"
#endif

class QuadPoint: public Point
{
public:
    double w;
    Eigen::MatrixXi N;
    Eigen::MatrixXi gradN;

    QuadPoint();
    QuadPoint(double weight, double *X);
    QuadPoint(double weight, double x, double y);
};

#endif // QUADPOINT_H
