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
    int z = line.at(1)[1] - 48;

    s.A = {ux, vy, z};
    s.B = {vx, vy, z};
    s.C = {vx, uy, z};
    s.D = {ux, uy, z};

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
    int z = line.at(1)[1] - 48;

    v.point = {ux, uy, z};

    Vias.push_back(v);
}


void Layer::move_obstacles_points() {
    for (int i = 0; i < (int)this->Obstacles.size(); i++) {
        Shape obs = Obstacles.at(i);
        Obstacles.at(i).A = {obs.A[0] - 1, obs.A[1] + 1, obs.A[2]};
        Obstacles.at(i).B = {obs.B[0] + 1, obs.B[1] + 1, obs.B[2]};
        Obstacles.at(i).C = {obs.C[0] + 1, obs.C[1] - 1, obs.C[2]};
        Obstacles.at(i).D = {obs.D[0] - 1, obs.D[1] - 1, obs.D[2]};

        if (Obstacles.at(i).A[0] < 0 || Obstacles.at(i).D[0] < 0 ||
            Obstacles.at(i).C[1] < 0 || Obstacles.at(i).D[1] < 0) {
            Obstacles.erase(Obstacles.begin() + i);
        }
    }
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


void print_vertex (Vertex v) {
    std::cout << "(" << v[0] << ", " << v[1] << ", " << v[2] << ")\n";
}
