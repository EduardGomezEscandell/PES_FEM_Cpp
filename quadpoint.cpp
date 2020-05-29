#include "quadpoint.h"

QuadPoint::QuadPoint():Point()
{
    // Invalid point (for instance to flag end of array).
    w = -1;
}

QuadPoint::QuadPoint(double weight, double *X) : Point(X)
{
    w = weight;
}

QuadPoint::QuadPoint(double weight, double x, double y=0) : Point(x,y)
{
    w = weight;
}
