#include <fstream>
#include <string>
#include <iostream>
#include "Circuit.h"
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>


void Circuit::draw(){
    for (std::map<string, Layer>::iterator it = Layers.begin(); it != Layers.end(); ++it) {
        std::cout << it->first << ":\n";
        std::cout << "Shapes:\n";
        it->second.print_shapes(1);
        std::cout << "Obstacles:\n";
        it->second.print_shapes(0);
        std::cout << "Vias:\n";
        it->second.print_vias();
        std::cout << "\n";
    }
}


void Circuit::input_to_objects(string case_path){
    std::ifstream fs(case_path);
    std::string line,  one, two, three, four;
    std::vector<std::string> input;
    std::vector<std::string> strs;

    while (std::getline(fs, line))
        input.push_back(line);


    boost::split(strs, input.at(0), boost::is_any_of("\t "));
    this->ViaCost = boost::lexical_cast<int>(strs.at(2));

    boost::split(strs, input.at(1), boost::is_any_of("\t "));
    this->Spacing = boost::lexical_cast<int>(strs.at(2));

    boost::split(strs, input.at(3), boost::is_any_of("\t "));
    this->N_MetalLayers = boost::lexical_cast<int>(strs.at(2));

    boost::split(strs, input.at(4), boost::is_any_of("\t "));
    this->N_RoutedShapes = boost::lexical_cast<int>(strs.at(2));

    boost::split(strs, input.at(5), boost::is_any_of("\t "));
    this->N_RoutedVias = boost::lexical_cast<int>(strs.at(2));

    boost::split(strs, input.at(6), boost::is_any_of("\t "));
    this->N_Obstacles = boost::lexical_cast<int>(strs.at(2));


    //  Cria as camadas no circuito (ainda vazias)
    for (int i = 1; i <= this->N_MetalLayers; i++) {
        Layer l;
        this->Layers["M" + std::to_string(i)] = l;
    }


    //  Instanciação dos objetos das Layers
    for (int i = 0; i < N_RoutedShapes; i++) {
        boost::split(strs, input.at(i + 7), boost::is_any_of("\t "));
        Layers[strs.at(1)].add_shape(strs);
    }

    int j = N_RoutedShapes + 7;
    for (int i = 0; i < N_RoutedVias; i++) {
        boost::split(strs, input.at(j + i), boost::is_any_of("\t "));
        Layers["M" + strs.at(1).substr(1, 1)].add_via(strs);

        std::string adj_layer = std::to_string(boost::lexical_cast<int>(strs.at(1).substr(1, 1)) + 1);
        Layers["M" + adj_layer].add_via(strs);
    }


    j = N_RoutedVias + N_RoutedShapes + 7;
    for (int i = 0; i < N_Obstacles; i++) {
        boost::split(strs, input.at(j + i), boost::is_any_of("\t "));
        Layers[strs.at(1)].add_shape(strs);

    }

    fs.close();
}


void Circuit::move_obstacles_points() {
    for (std::map<string, Layer>::iterator it = Layers.begin(); it != Layers.end(); ++it) {
        it->second.move_obstacles_points();
    }
}


G Circuit::generate_hanan_grid() {
    std::map<int, bool> X;
    std::map<int, bool> Y;
    std::map<Vertex, V> vertices;
    std::vector<Edge> grid;

    // Pega todos os pontos
    for (std::map<string, Layer>::iterator it = Layers.begin(); it != Layers.end(); ++it) {
        for (Shape c : it->second.Components) {
            X[c.A[0]] = 1;
            Y[c.A[1]] = 1;
            X[c.B[0]] = 1;
            Y[c.B[1]] = 1;
            X[c.C[0]] = 1;
            Y[c.C[1]] = 1;
            X[c.D[0]] = 1;
            Y[c.D[1]] = 1;
        }
        for (Shape o : it->second.Obstacles) {
            X[o.A[0]] = 1;
            Y[o.A[1]] = 1;
            X[o.B[0]] = 1;
            Y[o.B[1]] = 1;
            X[o.C[0]] = 1;
            Y[o.C[1]] = 1;
            X[o.D[0]] = 1;
            Y[o.D[1]] = 1;
        }
        for (Via v : it->second.Vias) {
            X[v.point[0]] = 1;
            Y[v.point[1]] = 1;
        }
    }


    // Adiciona as arestas entre os vizinhos
    for (std::map<int, bool>::iterator it_x = X.begin(); it_x != X.end(); ++it_x) {
        for (std::map<int, bool>::iterator it_y = Y.begin(); it_y != Y.end(); ++it_y) {
            std::map<int, bool>::iterator it_yp = it_y;
            ++it_yp;
            if (it_yp == Y.end()) {
                break;
            }

            Vertex u = {it_x->first, it_y->first, 0};
            Vertex v = {it_x->first, it_yp->first, 0};

            Edge e;
            e.u = u;
            e.v = v;
            e.w = euclidian_dist(u, v);
            grid.push_back(e);
            vertices[{it_x->first, it_y->first, 0}] = 1;
            vertices[{it_x->first, it_yp->first, 0}] = 1;
        }
    }


    // Adiciona as arestas entre os vizinhos
    for (std::map<int, bool>::iterator it_y = Y.begin(); it_y != Y.end(); ++it_y) {
        for (std::map<int, bool>::iterator it_x = X.begin(); it_x != X.end(); ++it_x) {
            std::map<int, bool>::iterator it_xp = it_x;
            ++it_xp;
            if (it_xp == X.end()) {
                break;
            }

            Vertex u = {it_x->first, it_y->first, 0};
            Vertex v = {it_xp->first, it_y->first, 0};

            Edge e;
            e.u = u;
            e.v = v;
            e.w = euclidian_dist(u, v);
            grid.push_back(e);
        }
    }

    G g;
    g.Vertex_map = vertices;
    g.Edges = grid;
    return g;
}
