#ifndef ELEMENTT1_H
#define ELEMENTT1_H
#include "element.h"
#include "quaddata.h"

class ElementT1: public Element
{
public:
    int n_nodes = 3;
    ElementT1(int element_id, Node* node_list, int *node_ids);
    double get_area();

    double * barycentric_to_cartesian(double L1, double L2, double L3);
    double * barycentric_to_cartesian(double *L);

    void initialize_shape_functions(QuadData *qdata);
};

#endif // ELEMENTT1_H
