#ifndef ELEMENT_H
#define ELEMENT_H
#include "node.h"
#include <stdlib.h>

class Element
{
public:
    int id;
    int n_nodes;
    Node* nodes;

    Element();
    Element(int element_id, Node* node_list, int *node_ids, int nodes_per_elem);

    double ** get_coordinates();
};

#endif // ELEMENT_H
