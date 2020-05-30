#ifndef ELEMENTT1_H
#define ELEMENTT1_H
#include "element.h"
#include "quaddata.h"

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

    Eigen::Matrix2d calc_jacobian();
//    void assemble(cooMat *K, QuadData *qdata);

    Eigen::Matrix2d get_jacobian();
    Eigen::Matrix2d get_invJacobian();
};

#endif // ELEMENTT1_H
