#include "quaddata.h"
#include <fstream> // ifstream
#include <stdlib.h> // stoi
#include <iostream>

QuadData::QuadData(std::string filename, int n_points_requested)
{
    /* Constructor that reads the quadarture points and weights from a txt file.
     * The quadrature will have either n_points_requested, or the immediate next available quadrature.
     */
    std::ifstream inputFile;
    inputFile.open(filename);

    if(!inputFile.is_open()){
        throw "Failed to load the quadrature data file";
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
            n_points_found = stoi(number_str); //Converting char to int
            if(n_points_found >= n_points_requested){
                success = true;
                break;
            }

        }
    }
    if(!success){
        throw "Failed to find a suitable quadrature. Try lowering n_points_requested or use a file with higher quadrature lists.";
    }

    QuadData::npoints = n_points_found;
    QuadData::points = (QuadPoint *) malloc( (QuadData::npoints+1) * sizeof(*points));

    // Reading values
    for(int i=0; i<n_points_found; i++){
        // Catching errors
        if(inputFile.eof() || getline(inputFile,line), line[0]=='n'){
            char errormsg [100];
            sprintf(errormsg, "Quadrature block (n = %d) has fewer points than indicated. Aborting.", n_points_found);
            throw errormsg;
        }
        // Reading values.
        char separator = '\t';
        std::vector<std::string> split_data = split_string(line, separator);

        if(split_data.size() < 2 || split_data.size() > 3){
            throw "Invalid math data file.";
        }

        double weight = stod(split_data[0]);

        double coordinates[2] = {0,0};
        for(size_t i=1; i<split_data.size(); i++){
            coordinates[i-1] =  stod(split_data[i]);
        }

        QuadData::points[i] = QuadPoint(weight, coordinates);
    }

    // Checking if all points were read
    if(!inputFile.eof() || getline(inputFile,line), line[0]!='n'){
        char errormsg [100];
        sprintf(errormsg, "Quadrature block (n = %d) has more points than indicated. Aborting.", n_points_found);
    }

    // Adding an end of array flag by adding an invalid weigth at the end
    QuadData::points[n_points_found] = QuadPoint();
}

std::vector<std::string> QuadData::split_string(std::string txt, char separator){
    /*
     *  This function splits a string 'txt' where a separator is located.
     * If the buffer runs out of space, the partition is ended. Stores the
     * partion in the buffer and returns the number of substrings.
     */
    std::vector<std::string> substrings;
    int start=0;
    int i;
    for(i=0; txt[i] != '\0'; i++){
        if(txt[i]==separator){
            if(i==start){
                // In case there are two consecutive separators, or a separator at the begining.
                start++;
            }
            else{
                // New partition
                std::string tmp = txt.substr(start, i-start);
                substrings.push_back(tmp);
                start = i+1;
            }
        }
    }
    // Appending last substring
    if(i > start){
        std::string tmp = txt.substr(start, i-start);
        substrings.push_back(tmp);
    }

    return substrings;
}
