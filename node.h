#ifndef NODE_H
#define NODE_H
#include "point.h"

#define BC_NONE 0
#define BC_DIRICHLET 1
#define BC_NEUMANN 2

class Node: public Point
{
public:
    int id;

    int bc_type = BC_NONE;
    double bc_value;

    Node();
    Node(int node_id, double *X);
    Node(int node_id, double x, double y);
};

#endif // NODE_H
