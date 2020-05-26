#ifndef ELEMENT_H
#define ELEMENT_H
#include "node.h"

class Element
{
public:
    int id;
    int n_nodes;
    Node* nodes;

    Element(int element_id, Node* node_list, int *node_ids);

    double ** get_coordinates();
};

#endif // ELEMENT_H
