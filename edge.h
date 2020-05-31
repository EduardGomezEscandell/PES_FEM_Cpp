#ifndef EDGE_H
#define EDGE_H

#include <math.h>

# include "node.h"
# include "quaddata.h"
#include <vector>

class Edge
{
public:
    int id;
    double length;
    int n_nodes;
    bool is_neumann;
    QuadData * qdata;
    std::vector<N_iterator> nodes;

    Edge(std::vector<int> node_ids, std::vector<N_iterator> node_list, QuadData * quadrature);
};

typedef std::vector<Edge>::iterator Eg_iterator;

#endif // EDGE_H
