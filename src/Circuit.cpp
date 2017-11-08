#include <fstream>
#include <string>
#include <iostream>
#include <utility>
#include "Circuit.h"
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <fstream>


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

    std::map<Vertex, V> vertices;
    std::set<Edge> grid;

    int z_coord = 1;

    std::cout << "   Getting the coordinates\n";
    // Pega todas as coordenadas
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

    G g(X.size() * Y.size() * Z.size());

    /*

    // Cria vértices e arestas
    for (int z : Z) {
        // Adiciona as arestas verticais
        for (std::set<int>::iterator it_x = X.begin(); it_x != X.end(); ++it_x) {
            for (std::set<int>::iterator it_y = Y.begin(); it_y != Y.end(); ++it_y) {
                std::set<int>::iterator it_yp = it_y;
                ++it_yp;
                if (it_yp == Y.end()) {
                    break;
                }

                Vertex u = {*it_x, *it_y, z};
                Vertex v = {*it_x, *it_yp, z};

                bool col = false;
                for (Shape o : Layers[z].Obstacles) {
                    if (point_collide_rect(u, o) || point_collide_rect(v, o)) {
                        col = true;
                        break;
                    }
                }

                if (!col) {
                    V vu;
                    V vv;
                    if (this->g.Vertex_map.find(u) == this->g.Vertex_map.end()) {
                        vu = boost::add_vertex(this->g.g);
                    }
                    else {
                        vu = this->g.Vertex_map[u];
                    }
                    if (this->g.Vertex_map.find(v) == this->g.Vertex_map.end()) {
                        vv = boost::add_vertex(this->g.g);
                    }
                    else {
                        vv = this->g.Vertex_map[v];
                    }

                    this->g.Vertex_map[u] = vu;
                    this->g.Vertex_map[v] = vv;
                    this->g.add_edge(vu, vv, euclidian_dist(u, v));
                }
                std::cout << "\r      " << ci << "/" << n_edges * N_MetalLayers;
                ci++;
            }
        }

        // Adiciona as arestas horizontais
        for (std::set<int>::iterator it_y = Y.begin(); it_y != Y.end(); ++it_y) {
            for (std::set<int>::iterator it_x = X.begin(); it_x != X.end(); ++it_x) {
                std::set<int>::iterator it_xp = it_x;
                ++it_xp;
                if (it_xp == X.end()) {
                    break;
                }

                Vertex u = {*it_x, *it_y, z};
                Vertex v = {*it_xp, *it_y, z};

                bool col = false;
                for (Shape o : Layers[z].Obstacles) {
                    if (point_collide_rect(u, o) || point_collide_rect(v, o)) {
                        col = true;
                        break;
                    }
                }

                if (!col) {
                    V vu;
                    V vv;
                    if (this->g.Vertex_map.find(u) == this->g.Vertex_map.end()) {
                        vu = boost::add_vertex(this->g.g);
                    }
                    else {
                        vu = this->g.Vertex_map[u];
                    }
                    if (this->g.Vertex_map.find(v) == this->g.Vertex_map.end()) {
                        vv = boost::add_vertex(this->g.g);
                    }
                    else {
                        vv = this->g.Vertex_map[v];
                    }

                    this->g.Vertex_map[u] = vu;
                    this->g.Vertex_map[v] = vv;
                    this->g.add_edge(vu, vv, euclidian_dist(u, v));
                }
                std::cout << "\r      " << ci << "/" << n_edges * N_MetalLayers;
                ci++;
            }
        }

        for (Via v : Layers[z].Vias) {
            Vertex uu = v.point;
            Vertex vv = uu;
            vv[2] = vv[2]++;
            print_v(vv);
            print_v(uu);
            this->g.add_edge(this->g.Vertex_map[uu], this->g.Vertex_map[uu], ViaCost);
        }
    }
    */

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


/*

void Circuit::close_components_cycles() {
    for () {

    }
}
















void Circuit::add_zero_edges_to_components(Set_Pair XY){
    std::cout << "Adding zero edges:\n";
    for (std::map<int, Layer>::iterator it = Layers.begin(); it != Layers.end(); ++it) {
        std::cout << "   " << it->first << ":\n";
        it->second.add_zero_edges_to_components(XY);
    }
}

void Circuit::convert_to_boost() {
    int i = 1, ne, n;
    std::cout << "Converting to boost graph\n";
    for (std::map<int, Layer>::iterator it = Layers.begin(); it != Layers.end(); ++it) {
        int camada = ((int)it->first[1] - 48); // pega o numero da camada (max 8 camadas)

        // Percorrer set de arestas, adicionar os vértices e as arestas
        n = it->second.g.Edges.size();
        ne = 1;
        for (Edge e : it->second.g.Edges) {
            std::cout << "\r      Layer " << i << "/" << Layers.size() << " - Edge " << ne << "/" << n;
            V vd_u, vd_v;
            E ed;

            e.u[2] = camada;
            e.v[2] = camada;

            //U
            if (g.Vertex_map.find(e.u) != g.Vertex_map.end()) { // Trocar
                vd_u = g.Vertex_map[e.u];
            }
            else {
                g.add_vertex(e.u);
                vd_u = g.Vertex_map[e.u];
            }
            //V
            if (g.Vertex_map.find(e.v) != g.Vertex_map.end()) { // Trocar
                vd_v = g.Vertex_map[e.v];
            }
            else {
                g.add_vertex(e.v);
                vd_v = g.Vertex_map[e.v];
            }

            g.add_edge(vd_u, vd_v, e.w);
            ne++;
        }

        // Adicionar as arestas das Vias
        if (i < (int)Layers.size()) {
            for (Via v : it->second.Vias) {
                Vertex vv = v.point;
                vv[2] = v.point[2] + 1; // Mesmo ponto, camada adjacente
                g.add_vertex(vv);
                g.add_edge(g.Vertex_map[v.point], g.Vertex_map[vv], ViaCost);
            }
        }
        i++;
        it->second.g.Edges.clear();
    }

    //g.print_Vertex_map();
    //g.print_edges_set();
}


void Circuit::remove_collision_with_obstacles(Set_Pair XY) {
    std::cout << "\nRemoving collisions with obstacles\n";
    std::set<Vertex> to_remove;
    for (std::map<int, Layer>::iterator it = Layers.begin(); it != Layers.end(); ++it) {
        std::cout << "   " << it->first << ":\n";
        to_remove = it->second.find_collision_with_obstacles(XY);

        for (Vertex v : to_remove) {
            g.remove_vertex(v);
        }
    }
}











//
*/
