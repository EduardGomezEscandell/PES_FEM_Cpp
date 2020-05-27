#include <iostream>
#include <stdlib.h> // atoi
#include "quaddata.h"

int main(int argc, char** argv)
{
    std::string filename = "../PES_FEM_Cpp/math_data/gauss_points_triangle.txt";
    int n_points = 5;
    if(argc>1){
        n_points = atoi(argv[1]);
    }
    QuadData qdata(filename, n_points);
    for(QuadPoint *q = qdata.points; q->w > 0; q++){
        std::cout<<"Weight "<<q->w<<"\tCoordinates: ("<<q->coordinates[0]<<", "<<q->coordinates[1]<<")"<<std::endl;
    }
}
