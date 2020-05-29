#ifndef DOMAIN_H
#define DOMAIN_H

#include "settings.h"

#include "elementt1.h"
#include "elementq2.h"

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
    size_t n_elemsT1;

//    ElementT2 * elementsT2;
    size_t n_elemsT2;

//    ElementQ1 * elementsQ1;
    size_t n_elemsQ1;

    ElementQ2 * elementsQ2;
    size_t n_elemsQ2;

    Node * nodes;
    size_t n_nodes;

    bool gradients_calculated = false;

    Domain(Settings settings);

    void printnodes();
    void printnodes(std::string filename);
    void printelems();
    void printelems(std::string filename);

    void calc_gradients(QuadData qdata_corners_T1);

    void export_result(std::string filename);

    size_t n_elems();

protected:
    void new_T1_element(int * node_ids, size_t * max_elem, size_t size_increment);
    void new_Q2_element(int * node_ids, size_t * max_elem, size_t size_increment);
};

#endif // DOMAIN_H
