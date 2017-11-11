#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include "Circuit.h"
#include <boost/graph/graphviz.hpp>





int main(int argc, char* argv[]){
    std::pair<std::set<int>, std::set<int>> XY;
    Circuit C;

    time_t start, end;
    time(&start);

    C.input_to_objects(argv[1]);
    C.move_obstacles_points();

    C.generate_hanan_grid();

    C.spanning_tree();

    string p = "print";
    if (argv[2] == p) {
        C.g.print_Vertex_map();
        //C.g.print_edges_set();
    }

    time(&end);
    double dif = difftime(end, start);
    std::cout << "\n\nTempo de execução: " << dif << " segundos\n";

    return 0;
}
