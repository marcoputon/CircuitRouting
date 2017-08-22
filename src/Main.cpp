#include <iostream>
#include <fstream>
#include <vector>
#include "Circuit.h"


int main(int argc, char* argv[]){
    Circuit C;
    C.input_to_objects(argv[1]);
    C.move_obstacles_points();
    G g = C.generate_hanan_grid();

    return 0;
}
