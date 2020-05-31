#ifndef DOMAIN_H
#define DOMAIN_H

#include "settings.h"

#include "node.h"

#include "elementt1.h"
#include "elementt2.h"
#include "elementq1.h"
#include "elementq2.h"

#include "aux_functions.h" // split_string

#include <stdio.h> // sprintf, fprintf
#include <vector>
#include <fstream>
#include <iostream>

typedef std::vector<ElementT1>::iterator T1_iterator;
typedef std::vector<ElementT2>::iterator T2_iterator;
typedef std::vector<ElementQ1>::iterator Q1_iterator;
typedef std::vector<ElementQ2>::iterator Q2_iterator;

class Domain
{
public:
    std::vector<ElementT1> elementsT1;
    std::vector<ElementT2> elementsT2;
    std::vector<ElementQ1> elementsQ1;
    std::vector<ElementQ2> elementsQ2;

    T1_iterator T1ptr();
    T2_iterator T2ptr();
    Q1_iterator Q1ptr();
    Q2_iterator Q2ptr();

    std::vector<Node> nodes;
    N_iterator Nptr();

    bool gradients_calculated = false;

    Domain(Settings settings, QuadData * quadratures);

    void printnodes();
    void printnodes(std::string filename);
    void printelems();
    void printelems(std::string filename);

    void calc_gradients();

    void export_result_dat(Settings settings);
    void export_result_vtk(Settings settings);

    size_t n_elems();
    size_t n_nodes();
};

// Using macro so I don't need to use basically the same method for all four element types
# define CALC_GRADIENT_LOCAL(E,qdata) do{                       \
    Eigen::VectorXd U_local(E->n_nodes);                        \
    for(int i=0; i<E->n_nodes; i++){                            \
        U_local(i) = E->nodes[i]->u;                            \
    }                                                           \
    std::vector<N_iterator>::iterator n = E->nodes.begin();     \
    for(qiterator q=qdata->pointsptr(); q->w >= 0; q++){         \
        Eigen::MatrixXd gradN = E->get_invJacobian(*q) * q->gradN;\
        (**n).grad_u += gradN * U_local;                        \
        n++;                                                    \
    }                                                           \
}while(0);


#endif // DOMAIN_H
