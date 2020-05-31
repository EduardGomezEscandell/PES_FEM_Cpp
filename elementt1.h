#ifndef ELEMENTT1_H
#define ELEMENTT1_H

#include "element.h"

class QuadData;

class ElementT1: public Element
{
public:
    const int vtk_id = 5; // ID used by paraview to identify the element type

    ElementT1();
    ElementT1(int element_id, std::vector<Node> * node_list, std::vector<int> node_ids);

    double * barycentric_to_cartesian(double L1, double L2, double L3);
    double * barycentric_to_cartesian(double *L);
    double * barycentric_to_cartesian(double *L, double ** corners);

    Edge get_edge(int i);

    Eigen::Matrix2d calc_jacobian();
    Eigen::Matrix2d get_jacobian(QuadPoint q);
    Eigen::Matrix2d get_invJacobian(QuadPoint q);
};

#endif // ELEMENTT1_H
