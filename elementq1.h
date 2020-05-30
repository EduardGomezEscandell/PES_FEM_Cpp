#ifndef ELEMENTQ1_H
#define ELEMENTQ1_H

#include "element.h"
#include "dependencies/Eigen/Dense"

class ElementQ1 : public Element
{
public:
    const int vtk_id = 9; // ID used by paraview to identify the element type

    ElementQ1();
    ElementQ1(int element_id, std::vector<Node> * node_list, std::vector<int> node_ids);

    Eigen::Matrix2d calc_jacobian();
    Eigen::Matrix2d get_jacobian();
    Eigen::Matrix2d get_invJacobian();
};

#endif // ELEMENTQ1_H
