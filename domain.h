#ifndef DOMAIN_H
#define DOMAIN_H
#include "element.h"
#include "elementt1.h"

#include "node.h"
#include "aux_functions.h" // split_string

#include <stdio.h> // sprintf
#include <vector>
#include <fstream>
#include <iostream>

class Domain
{
public:
    ElementT1 * elementsT1;
    size_t n_elems;

    Node * nodes;
    size_t n_nodes;

    Domain(std::string node_file, std::string mesh_file);

    void printnodes();
    void printnodes(std::string filename);

    void printelems();
    void printelems(std::string filename);
};

#endif // DOMAIN_H
