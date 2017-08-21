#include "Layer.h"
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

void Layer::add_shape(std::vector<string> line) {
    Shape s;
    std::vector<string> splited;

    boost::split(splited, line.at(2), boost::is_any_of("\t,"));
    int ux = boost::lexical_cast<int>(splited.at(0).substr(1, splited.at(0).size() - 1));
    int uy = boost::lexical_cast<int>(splited.at(1).substr(0, splited.at(1).size() - 1));

    boost::split(splited, line.at(3), boost::is_any_of("\t,"));
    int vx = boost::lexical_cast<int>(splited.at(0).substr(1, splited.at(0).size() - 1));
    int vy = boost::lexical_cast<int>(splited.at(1).substr(0, splited.at(1).size() - 1));

    // Máximo 8 camadas, 1 indice da string
    int z = boost::lexical_cast<int>(line.at(1).substr(1, 1));


    s.A = {vx, uy, z};
    s.B = {ux, uy, z};
    s.C = {ux, vy, z};
    s.D = {vx, vy, z};

    Shapes.push_back(s);
    /*
*/
}

void print_v(Vertex v) {
    std::cout << "(" << v[0] << ", " << v[1] << ", " << v[2] << ")\n";
}

void Layer::print_shapes() {
    for (Shape s : Shapes) {
        print_v(s.A);
        print_v(s.B);
        print_v(s.C);
        print_v(s.D);
    }
}
