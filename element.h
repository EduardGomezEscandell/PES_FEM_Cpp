#ifndef ELEMENT_H
#define ELEMENT_H
#include "node.h"
#include <stdlib.h>

#include <vector>
#include "quaddata.h"
#include "dependencies/Eigen/Dense"
#include "dependencies/Eigen/Sparse"
typedef std::vector<Eigen::Triplet<double>> cooMat; //Typedef'd COO matrix

typedef std::vector<Node>::iterator N_iterator; // Typedef'd pointer to node in vector

class Element
{
public:
    int id;
    int n_nodes;

    std::vector<N_iterator> nodes;
    double area;

    bool jacobian_is_calculated = false;

    Element();
    Element(int element_id, std::vector<Node> * node_list, std::vector<int> node_ids, int nodes_per_elem);

    double ** get_coordinates();

    int connectivity_line_vtk(char * buffer);

protected:
    Eigen::Matrix2d jacobian;
    Eigen::Matrix2d invJacobian;
};

#endif // ELEMENT_H
