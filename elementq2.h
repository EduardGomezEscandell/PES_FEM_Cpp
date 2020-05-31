#ifndef ELEMENTQ2_H
#define ELEMENTQ2_H

#include "element.h"

#include "dependencies/Eigen/Dense"

class ElementQ2 : public Element
{
public:
    const int vtk_id = 28; // ID used by paraview to identify the element type

    ElementQ2();
    ElementQ2(int element_id, std::vector<Node> * node_list, std::vector<int> node_ids);

    Edge get_edge(int i);

    Eigen::Matrix2d calc_jacobian();
    Eigen::Matrix2d get_jacobian(QuadPoint q);
    Eigen::Matrix2d get_invJacobian(QuadPoint q);

    int consecutive_node(int i);
};

#endif // ELEMENTQ2_H
