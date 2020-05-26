#include "node.h"

Node::Node(int node_id, double *X) : Point(X)
{
    id = node_id;
}

Node::Node(int node_id, double x, double y=0, double z=0) : Point(x,y,z)
{
    id = node_id;
}
