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
    int z = boost::lexical_cast<int>(line.at(1).substr(1, 1));

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




std::set<Edge> interval (Set_Pair XY, Vertex A, Vertex B, Vertex C) {
    Vector_Pair inter;
    std::set<int> X, Y;
    std::set<Edge> edges;

    // subX
    for (std::set<int>::iterator it = XY.first.find(A[0]); it != XY.first.find(B[0]); ++it) {
        X.insert(*it);
    }
    X.insert(B[0]);
    // subY
    for (std::set<int>::iterator it = XY.second.find(C[1]); it != XY.second.find(B[1]); ++it) {
        Y.insert(*it);
    }
    Y.insert(B[1]);


    // Cria grade de hanan com pesos 0 para X e Y

    // Adiciona as arestas verticais
    for (std::set<int>::iterator it_x = X.begin(); it_x != X.end(); ++it_x) {
        for (std::set<int>::iterator it_y = Y.begin(); it_y != Y.end(); ++it_y) {
            std::set<int>::iterator it_yp = it_y;
            ++it_yp;
            if (it_yp == Y.end()) {
                break;
            }

            Vertex u = {*it_x, *it_y, A[2]};
            Vertex v = {*it_x, *it_yp, A[2]};

            Edge e;
            e.u = u;
            e.v = v;
            e.w = 0;
            edges.insert(e);
        }
    }

    // Adiciona as arestas horizontais
    for (std::set<int>::iterator it_y = Y.begin(); it_y != Y.end(); ++it_y) {
        for (std::set<int, bool>::iterator it_x = X.begin(); it_x != X.end(); ++it_x) {
            std::set<int, bool>::iterator it_xp = it_x;
            ++it_xp;
            if (it_xp == X.end()) {
                break;
            }

            Vertex u = {*it_x, *it_y, A[2]};
            Vertex v = {*it_xp, *it_y, A[2]};

            Edge e;
            e.u = u;
            e.v = v;
            e.w = 0;
            edges.insert(e);
        }
    }

    return edges;
}







/*
*/

void Layer::add_zero_edges_to_components(Set_Pair XY) {
    std::set<Edge> z_edges;
    int n = this->Components.size();
    //std::cout << "Caiu na funcao. Numero de componentes: " << n << "\n";
    int count = 1;
    for (Shape c : this->Components) {
        std::cout << "\r      Shape " << count << "/" << n;
        z_edges = interval(XY, c.A, c.B, c.C);

        count++;
    }
    //std::cout << "\nPassou do FOR\n";
    std::cout << "\n";
}














//
