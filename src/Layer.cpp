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

    if (line.at(0) == "Obstacle")
        Obstacles.push_back(s);
    else
        Components.push_back(s);
}

void Layer::add_via(std::vector<string> line) {
    Via v;
    std::vector<string> splited;

    boost::split(splited, line.at(2), boost::is_any_of("\t,"));
    int ux = boost::lexical_cast<int>(splited.at(0).substr(1, splited.at(0).size() - 1));
    int uy = boost::lexical_cast<int>(splited.at(1).substr(0, splited.at(1).size() - 1));

    // Máximo 8 camadas, 1 indice da string
    int z = boost::lexical_cast<int>(line.at(1).substr(1, 1));

    v.point = {ux, uy, z};

    Vias.push_back(v);
}

void print_v(Vertex v) {
    std::cout << "(" << v[0] << ", " << v[1] << ", " << v[2] << ")\n";
}

void Layer::print_shapes(bool sh) {
    if (sh) {
        for (Shape s : Components) {
            print_v(s.A);
            print_v(s.B);
            print_v(s.C);
            print_v(s.D);
        }
    }
    else {
        for (Shape s : Obstacles) {
            print_v(s.A);
            print_v(s.B);
            print_v(s.C);
            print_v(s.D);
        }
    }
}

void Layer::print_vias() {
    for (Via v : Vias) {
        print_v(v.point);
    }
}
