#ifndef ELEMENT_H
#define ELEMENT_H
#include "node.h"
#include <stdlib.h>

#include <vector>
#include "dependencies/Eigen/Dense"
#include "dependencies/Eigen/Sparse"
typedef std::vector<Eigen::Triplet<double>> cooMat; //Typedef'd COO matrix

class Element
{
public:
    int id;
    int n_nodes;

    Node ** nodes;
    double area;

    bool jacobian_is_calculated = false;

    Eigen::Matrix2d jacobian;
    Eigen::Matrix2d invJacobian;

    Element();
    Element(int element_id, Node* node_list, int *node_ids, int nodes_per_elem);

    double ** get_coordinates();
};

#endif // ELEMENT_H
