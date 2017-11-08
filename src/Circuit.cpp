#include <fstream>
#include <string>
#include <iostream>
#include <utility>
#include "Circuit.h"
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <fstream>
#include <unordered_map>


void Circuit::draw(){
    for (std::map<int, Layer>::iterator it = Layers.begin(); it != Layers.end(); ++it) {
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
    std::cout << "Generating objects from input\n";
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
        this->Layers[i] = l;
    }

    //  Instanciação dos objetos das Layers
    for (int i = 0; i < N_RoutedShapes; i++) {
        boost::split(strs, input.at(i + 7), boost::is_any_of("\t "));
        Layers[strs.at(1)[1] - 48].add_shape(strs);
    }

    int j = N_RoutedShapes + 7;
    for (int i = 0; i < N_RoutedVias; i++) {
        boost::split(strs, input.at(j + i), boost::is_any_of("\t "));
        Layers[strs.at(1)[1] - 48].add_via(strs);

        Layers[strs.at(1)[1] - 47].add_via(strs);
    }

    j = N_RoutedVias + N_RoutedShapes + 7;
    for (int i = 0; i < N_Obstacles; i++) {
        boost::split(strs, input.at(j + i), boost::is_any_of("\t "));
        Layers[strs.at(1)[1] - 48].add_shape(strs);

    }
    fs.close();
}



void Circuit::move_obstacles_points() {
    std::cout << "Moving obstacle points\n";
    for (std::map<int, Layer>::iterator it = Layers.begin(); it != Layers.end(); ++it) {
        it->second.move_obstacles_points();
    }
}


bool point_collide_rect(Vertex v, Shape s) {
    return ((v[0] > s.A[0] && v[0] < s.B[0]) && (v[1] > s.D[1] && v[1] < s.A[1]));
}

void Circuit::generate_hanan_grid() {
    std::cout << "Generating hanan grid\n";

    std::set<int> X;
    std::set<int> Y;
    std::set<int> Z;

    std::vector<Vertex> vertices;
    std::map<Vertex, int> rev_map;
    std::set<Edge> grid;

    int z_coord = 1;

    for (std::map<int, Layer>::iterator it = Layers.begin(); it != Layers.end(); ++it) {
        for (Shape c : it->second.Components) {
            X.insert(c.A[0]);
            Y.insert(c.A[1]);
            X.insert(c.B[0]);
            Y.insert(c.B[1]);
            X.insert(c.C[0]);
            Y.insert(c.C[1]);
            X.insert(c.D[0]);
            Y.insert(c.D[1]);
        }
        for (Shape o : it->second.Obstacles) {
            X.insert(o.A[0]);
            Y.insert(o.A[1]);
            X.insert(o.B[0]);
            Y.insert(o.B[1]);
            X.insert(o.C[0]);
            Y.insert(o.C[1]);
            X.insert(o.D[0]);
            Y.insert(o.D[1]);
        }
        for (Via v : it->second.Vias) {
            X.insert(v.point[0]);
            Y.insert(v.point[1]);
        }
        Z.insert(z_coord);
        z_coord++;
    }

    Graph g(X.size() * Y.size() * Z.size());

    for (int x : X) {
        for (int y : Y) {
            for (int z : Z) {
                vertices.push_back({x,y,z});
                rev_map[{x,y,z}] = vertices.size() - 1;
            }
        }
    }


    //
    // for (int x : X) {
    //     for (int y : Y) {
    //         add_edge()
    //     }
    // }


}



void Circuit::spanning_tree() {
    std::ofstream myfile;
    myfile.open("spanning.dot");
    myfile << "graph {\n";

    std::vector <E> spanning_tree;
    boost::kruskal_minimum_spanning_tree(this->g.g, std::back_inserter(spanning_tree));

    for (std::vector<E>::iterator ei = spanning_tree.begin(); ei != spanning_tree.end(); ++ei) {
        myfile << source(*ei, this->g.g) << " -- " << target(*ei, this->g.g) << "\n";
    }
    myfile << "}";
    myfile.close();
}
