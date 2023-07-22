# GMSH Reader
A fast and efficient code for reading [GMSH](https://gmsh.info/) msh2 format triangular meshes. The code uses only inbuilt C++ function and headers. The connectivity matrix 
is stored in `size_t` array, which can be used with domain decomposition libraries (for instance [METIS](https://github.com/KarypisLab/METIS)

## MSH2 Generation
To generate a 2D msh2 format mesh, use the following command:
```
    gmsh filename.geo -format msh2 -2 -o output_filename.msh
```

## Example Code
An example use of the code using `flow_past_cylinder.msh` in `assets` folder is shown here
```
    #include "gmsh_reader.hpp"

    int main() {
    std::unique_ptr<Mesh> m = std::make_unique<Mesh>("../assets/flow_past_cylinder.msh");
    return 0;
    }
````
