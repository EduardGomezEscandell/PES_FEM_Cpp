#ifndef NODE_H
#define NODE_H
#include "point.h"

class Node: public Point
{
public:
    int id;
    Node();
    Node(int node_id, double *X);
    Node(int node_id, double x, double y);
};

#endif // NODE_H
