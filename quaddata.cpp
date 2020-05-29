#include "quaddata.h"

QuadData::QuadData(size_t n_nodes)
{
    // Quadrature lumped at the nodes
    npoints = (int) n_nodes;

    switch (npoints){
    case 3:
        points.emplace_back(1, 0, 0);
        points.emplace_back(1, 1, 0);
        points.emplace_back(1, 0, 1);
        points.emplace_back();
        break;
    case 4:
        // Todo
    case 6:
        // Todo
    case 9:
        // Todo
        break;
    default:
        throw "Only linear and quadratic, triangular and quadrilateral elements allowed";
    }
}

QuadData::QuadData(std::string filename, int n_points_requested)
{
    /*
     * Constructor that reads the quadarture points and weights from a txt file.
     * The quadrature will have either n_points_requested, or the immediate next available quadrature.
     */
    std::ifstream inputFile;
    inputFile.open(filename);

    if(!inputFile.is_open()){
        std::cerr<<"Failed to load the quadrature data file"<<std::endl;
        throw -1;
    }

    std::string line;

    // Searching for start of block
    int n_points_found = -1;
    bool success = false;
    while(!inputFile.eof()){
        // Looping until EOF (end of file)
        getline(inputFile, line);
        if(line[0] == 'n')
        {
             // Line is "n = NUMBER". Reading NUMBER up to 10 characters should be by far sufficient.
            std::string number_str = line.substr(4,10);
            n_points_found = std::stoi(number_str); //Converting string to int
            if(n_points_found >= n_points_requested){
                success = true;
                break;
            }

        }
    }
    if(!success){
        std::cerr<<"Failed to find a suitable quadrature. Try lowering n_points_requested or use a file with higher quadrature lists."<<std::endl;
        throw -1;
    }

    npoints = n_points_found;

    // Reading values
    for(int i=0; i<npoints; i++){
        // Catching errors
        if(inputFile.eof() || getline(inputFile,line), line[0]=='n'){
            char errormsg [100];
            sprintf(errormsg, "Quadrature block (n = %d) has fewer points than indicated. Aborting.", n_points_found);
            std::cerr<<errormsg<<std::endl;
            throw -1;
        }
        // Reading values.
        char separator = '\t';
        std::vector<std::string> split_data = split_string(line, separator);

        if(split_data.size() < 2 || split_data.size() > 3){
            std::cerr<<"Invalid math data file."<<std::endl;
            throw -1;
        }

        double weight = stod(split_data[0]);

        double coordinates[2] = {0,0};
        for(size_t i=1; i<split_data.size(); i++){
            coordinates[i-1] =  stod(split_data[i]);
        }

        points.emplace_back(weight, coordinates);
    }

    // Checking if all points were read
    if(!inputFile.eof() || getline(inputFile,line), line[0]!='n'){
        char errormsg [100];
        sprintf(errormsg, "Quadrature block (n = %d) has more points than indicated. Aborting.", n_points_found);
    }

    inputFile.close();

    // Adding an end of array sentinel by adding an invalid weight at the end
    points.emplace_back();
}


qiterator QuadData::pointsptr(){
    return points.begin();
}

//void QuadData::square_quadrature(){
//    // Turns a segment quadrature into a square quadrature. Shape functions must be calculated afterwards.
//    int new_npoints = npoints*npoints;
//    QuadPoint *new_points = (QuadPoint *) malloc( (new_npoints+1) * sizeof(QuadPoint));

//    int k = 0;

//    double coords[] = {0,0};

//    for(qiterator qi = pointsptr(); qi->w > 0; qi++){
//        coords[0] = qi->coordinates[0];

//        for(qiterator qj = pointsptr(); qj->w > 0; qj++){
//            coords[1] = qj->coordinates[0];

//            double w = qi->w * qj->w;
//            new_points[k] = QuadPoint(w, coords);
//            k++;
//        }
//    }

//    // Adding an end of array sentinel by adding an invalid weight at the end
//    new_points[k] = QuadPoint();

//    points = new_points;
//    npoints = new_npoints;
//    free(new_points);
//}




void QuadData::initialize_shape_functions(int n_functions){

    // Obtaining sum of weights (used for integration)
    total_weight = 0;

    // Corners for the shape functions
    double corners[3][2]= {{0,0},{1,0},{0,1}};

    // Looping obtaining shape fun for all integration points;
    for(qiterator q = pointsptr(); q->w > 0; q++){
        total_weight += q->w;

        double *X = barycentric_to_cartesian(q->coordinates, corners);
        double x = X[0];
        double y = X[1];

        // Shape functions
        q->N = Eigen::MatrixXd(1, n_functions);
        q->N(0) = 1 - x - y;
        q->N(1) = x;
        q->N(2) = y;

        // Gradient
        q->gradN = Eigen::MatrixXd(2, n_functions);
        // N1
        q->gradN(0,0) = -1;
        q->gradN(1,0) = -1;
        // N2
        q->gradN(0,1) =  1;
        q->gradN(1,1) =  0;
        // N3
        q->gradN(0,2) =  0;
        q->gradN(1,2) =  1;
    }
}





