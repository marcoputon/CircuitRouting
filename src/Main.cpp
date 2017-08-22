#include <iostream>
#include <fstream>
#include <vector>
#include "Circuit.h"


int main(){
    Circuit C;
    C.input_to_objects("../cases/case0");
    C.draw();
    C.move_obstacles_points();
    std::cout << "\n";
    C.draw();

    return 0;
}
