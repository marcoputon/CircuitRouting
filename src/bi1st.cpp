#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include "lib/Circuit.h"
#include <boost/graph/graphviz.hpp>



int main(int argc, char* argv[]){
    std::pair<std::set<int>, std::set<int>> XY;
    Circuit C;

    time_t start, end;
    time(&start);

    C.input_to_objects(argv[1]);
    C.move_obstacles_points();
    C.generate_hanan_grid(false);
    C.connect_all_components();




    time(&end);
    double dif = difftime(end, start);
    std::cout << "\n\nTempo de execução: " << dif << " segundos\n";

    return 0;
}