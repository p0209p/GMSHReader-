#include "gmsh_reader.hpp"

std::vector<std::string> split(std::string str, std::string delim) {
    std::istringstream s ( str);
    std::vector<std::string> result;
    result.insert(result.end(), 
                 std::istream_iterator<std::string>(s),  
                 std::istream_iterator<std::string>());
    return result;
}

Mesh::Mesh(std::string filename) {
    try {
        std::ifstream f(filename);
        std::string line; 
        std::vector<std::string> split_string;
        getline(f, line); // $MeshFormat
        getline(f, line); // Version no. File type size_of_floating_point
        split_string = split(line," ");
        if (std::floor(std::stof(split_string[0])) != 2) {
            std::cerr<<"Invalid file format ! the reader can only parse MSH2 format meshes\n";
            exit(1);
        }
        getline(f, line); // $EndMeshFormat
        getline(f, line); // $PhysicalNames
        getline(f, line); // No of physical named regions
        size_t no_of_names = std::stoull(line);
        unsigned int nelementary_temp = 0; // Temp variable to store the no of Physical Lines
        for(unsigned int i = 0;i < no_of_names; ++i) {
            getline(f, line);
            split_string = split(line, " ");
            if (std::stoull(split_string[0]) == 1) {
                nelementary_temp += 1;
                boundary_id.push_back(std::stoull(split_string[1]));
                boundary_names.push_back(split_string[2].substr(1,split_string[2].length()-2));
            }
            else {
                domain_id = std::stoull(split_string[1]);
                domain_name = split_string[2].substr(1,split_string[2].length()-2);
            }
        }
        for(unsigned int i=0;i<nelementary_temp;++i) {
            boundary_nodes.push_back(std::set<size_t>());
        }
        getline(f, line); // $EndPhysicalNames
        getline(f, line); // $Nodes
        getline(f, line); // No of coordinates
        no_of_coords = std::stoull(line);
        coords = new double[no_of_coords*2];
        for(size_t i = 0;i < no_of_coords;++i) {
            getline(f, line);
            split_string = split(line, " ");
            coords[2*i] = std::stod(split_string[1]);
            coords[2*i+1] = std::stod(split_string[2]);
        }
        getline(f, line); // $EndNodes
        getline(f, line); // $Elements
        getline(f, line); // No of elements
        size_t element_no = 0;
        size_t ne = std::stoull(line);
        size_t i = 0;
        for(i=0;i<ne;++i) {
            getline(f, line);
            split_string = split(line, " ");
            if (std::stoull(split_string[1]) == 2)
                break;
            auto it = std::find(boundary_id.begin(),boundary_id.end(),std::stoi(split_string[3]));
            if(it != boundary_id.end()) {
                size_t index = std::distance(boundary_id.begin(), it);
                for(auto j=index;j<split_string.size();++j) {
                    boundary_nodes[index].insert(std::stoull(split_string[j]));
                }
            }
        }
        no_of_elements = ne - i;
        conn = new size_t[no_of_elements*3];
        conn[element_no] = std::stoull(split_string[5]);
        conn[element_no+1] = std::stoull(split_string[6]);
        conn[element_no+2] = std::stoull(split_string[7]);
        element_no += 3;
        i += 1;
        for(;i<ne;++i) {
            getline(f, line);
            split_string = split(line, " ");
            conn[element_no] = std::stoull(split_string[5]);
            conn[element_no+1] = std::stoull(split_string[6]);
            conn[element_no+2] = std::stoull(split_string[7]);
            element_no += 3;
        }
        f.close();
    }
    catch (std::runtime_error& msg) {
        std::cerr<<"Exception caught: "<<msg.what()<<"\n";
    }
}

Mesh::~Mesh() {
    delete[] coords;
    delete[] conn;
}
