#ifndef ELEMENTT1_H
#define ELEMENTT1_H
#include "element.h"

class ElementT1: public Element
{
public:
    int n_nodes = 3;
    ElementT1(int element_id, Node* node_list, int *node_ids);
    double get_area();
};

#endif // ELEMENTT1_H
