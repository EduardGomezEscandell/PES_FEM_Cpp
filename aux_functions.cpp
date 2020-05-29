#include "aux_functions.h"

std::vector<std::string> split_string(std::string txt, char separator){
    /*
     *  This function splits a string 'txt' where a separator is located.
     *  Returns a vector of strings.
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

double *barycentric_to_cartesian(double *L, double corners[3][2]){
    // Returns a ponter to the coordinates in cartesian. Remember to free the pointer afterwards!
    static double cartesian[2];
    double L2 = 1 - L[0] - L[1];
    for(int i=0; i<3; i++){
        cartesian[i] = L[0] * corners[0][i]
                     + L[1] * corners[1][i]
                     +  L2  * corners[2][i];
    }
    return *(&cartesian);
}

