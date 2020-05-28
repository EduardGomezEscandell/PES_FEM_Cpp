#include "node.h"

Node::Node()
{
    id = -1;
    // Invalid node to use as sentinel
}


Node::Node(int node_id, double *X) : Point(X)
{
    id = node_id;
}

Node::Node(int node_id, double x, double y=0) : Point(x,y)
{
    id = node_id;
}
