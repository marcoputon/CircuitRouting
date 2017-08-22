#include <iostream>
#include <fstream>
#include <vector>
#include "Circuit.h"


int main(){
    Circuit C;
    C.input_to_objects("../cases/case1");
    C.draw();

    return 0;
}
