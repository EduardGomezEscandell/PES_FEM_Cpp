#ifndef ELEMENT_H
#define ELEMENT_H
#include "node.h"
#include <stdlib.h>

#include <vector>
#include "dependencies/Eigen/Dense"
#include "dependencies/Eigen/Sparse"

#include "quaddata.h"
#include "edge.h"



typedef std::vector<Eigen::Triplet<double>> cooMat; //Typedef'd COO matrix

class Element
{
public:
    int id;
    int n_nodes;
    double area;

    std::vector<N_iterator> nodes;
    QuadData * qdata;
    QuadData * qdata_line;

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
