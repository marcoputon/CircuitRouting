#include <iostream>
#include <fstream>
#include <vector>
#include "Circuit.h"


int main(){
    Circuit C;
    C.input_to_objects("../cases/case-1");
    C.move_obstacles_points();
    C.generate_hanan_grid();

    return 0;
}
