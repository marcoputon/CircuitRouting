#include <iostream>
#include <fstream>
#include <vector>
#include "Circuit.h"


int main(int argc, char* argv[]){
    Circuit C;
    C.input_to_objects(argv[1]);
    C.move_obstacles_points();
    C.generate_hanan_grid();
    C.add_zero_edges_to_components();


    string p = "print";
    if (argv[2] == p) {
        for (std::map<string, Layer>::iterator it = C.Layers.begin(); it != C.Layers.end(); ++it) {
            it->second.g.print_Vertex_map();
            it->second.g.print_edges();
        }
    }

    return 0;
}
