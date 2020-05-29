#include "element.h"

Element::Element(){
    // Invalid element to use as sentinel
    id = -1;
}

Element::Element(int element_id, Node* node_list, int *node_ids, int nodes_per_elem)
// Initializes an element with its connectivity
{
    id = element_id;
    n_nodes = nodes_per_elem;
    nodes = (Node **)malloc(n_nodes * sizeof (*nodes));
    for(int i=0; i<n_nodes; i++){
        nodes[i] = &(node_list[node_ids[i]]);
    }
}

double ** Element::get_coordinates(){
    // Returns an array with the coordinates of its nodes. Shape: [node][axis]
    double** X = (double **) malloc(n_nodes * sizeof(double*));
    for(int i=0; i<n_nodes; i++){
        X[i] = nodes[i]->coordinates;
    }
    return X;
}
