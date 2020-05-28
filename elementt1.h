#ifndef ELEMENTT1_H
#define ELEMENTT1_H
#include "element.h"
#include "dependencies/Eigen/Dense"

class QuadData;

class ElementT1: public Element
{
public:
    int n_nodes = 3;
    bool jacobian_is_calculated = false;
    Eigen::Matrix2d jacobian;

    ElementT1();
    ElementT1(int element_id, Node* node_list, int* node_ids);

    double get_area();

    double * barycentric_to_cartesian(double L1, double L2, double L3);
    double * barycentric_to_cartesian(double *L);
    double * barycentric_to_cartesian(double *L, double ** corners);

    Eigen::Matrix2d calc_jacobian();
};

#endif // ELEMENTT1_H
