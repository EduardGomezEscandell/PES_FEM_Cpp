#ifndef ELEMENTT2_H
#define ELEMENTT2_H

#include "element.h"
#include "dependencies/Eigen/Dense"

class ElementT2 : public Element
{
public:
    const int vtk_id = 22; // ID used by paraview to identify the element type

    ElementT2();
    ElementT2(int element_id, std::vector<Node> * node_list, std::vector<int> node_ids);

    Eigen::Matrix2d calc_jacobian();
    Eigen::Matrix2d get_jacobian();
    Eigen::Matrix2d get_invJacobian();
};

#endif // ELEMENTT2_H
