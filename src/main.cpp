#include "gmsh_reader.hpp"

int main() {
    std::unique_ptr<Mesh> m = std::make_unique<Mesh>("../assets/flow_past_cylinder.msh");
    return 0;
}
