#include "edge.h"

Edge::Edge(std::vector<int> node_ids, std::vector<N_iterator> node_list, QuadData * quadrature)
{
    n_nodes = node_ids.size();

    for(int i=0; i<n_nodes; i++){
        int node_id = node_ids[i];
        N_iterator node_ptr = node_list[node_id];
        nodes.push_back(node_ptr);
    }

    qdata = quadrature;

    double dX = nodes[0]->coordinates[0] - nodes.back()->coordinates[0];
    double dY = nodes[0]->coordinates[1] - nodes.back()->coordinates[1];

    length = sqrt(dX*dX + dY*dY);

    // Checking if it is neumann
    is_neumann = true;
    for(int i=0; i<n_nodes; i++){
        if (nodes[i]->bc_type != BC_NEUMANN){
            is_neumann = false;
            break;
        }
    }

}
