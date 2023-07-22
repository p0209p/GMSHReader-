#ifndef GMSH_READER
#define GMSH_READER

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <cmath>
#include <memory>
#include <sstream>
#include <iterator>

class Mesh {
    public:
        size_t no_of_coords;
        size_t no_of_elements;
        double* coords;
        std::vector<std::string> boundary_names;
        std::string domain_name;
        unsigned int domain_id;
        std::vector<unsigned int> boundary_id;
        std::vector<std::set<size_t>> boundary_nodes;
        size_t* conn;
        Mesh(std::string filename);
        ~Mesh();
};

std::vector<std::string> split(const std::string str,const std::string delim);

#endif 
