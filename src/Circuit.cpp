#include <fstream>
#include <string>
#include <iostream>
#include <utility>
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
    std::cout << "Moving obstacle points\n";
    for (std::map<string, Layer>::iterator it = Layers.begin(); it != Layers.end(); ++it) {
        it->second.move_obstacles_points();
    }
}


Set_Pair Circuit::generate_hanan_grid() {
    std::cout << "Generating hanan grid\n";
    std::set<int> X;
    std::set<int> Y;
    std::map<Vertex, V> vertices;
    std::set<Edge> grid;
    G g;

    std::cout << "   Getting the coordinates\n";
    // Pega todos os pontos
    for (std::map<string, Layer>::iterator it = Layers.begin(); it != Layers.end(); ++it) {
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
    }

    int ci = 1, n_edges = (X.size()-1) * Y.size() + (Y.size()-1) * X.size();
    std::cout << "   Creating edges\n";
    // Adiciona as arestas verticais
    for (std::set<int>::iterator it_x = X.begin(); it_x != X.end(); ++it_x) {
        for (std::set<int>::iterator it_y = Y.begin(); it_y != Y.end(); ++it_y) {
            std::set<int>::iterator it_yp = it_y;
            ++it_yp;
            if (it_yp == Y.end()) {
                break;
            }

            Vertex u = {*it_x, *it_y, 0};
            Vertex v = {*it_x, *it_yp, 0};

            Edge e;
            e.u = u;
            e.v = v;
            e.w = euclidian_dist(u, v);
            grid.insert(e);
            vertices[{*it_x, *it_y, 0}] = boost::add_vertex(g.g);
            vertices[{*it_x, *it_yp, 0}] = boost::add_vertex(g.g);
            std::cout << "\r      " << ci << "/" << n_edges;
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

            Vertex u = {*it_x, *it_y, 0};
            Vertex v = {*it_xp, *it_y, 0};

            Edge e;
            e.u = u;
            e.v = v;
            e.w = euclidian_dist(u, v);
            grid.insert(e);
            std::cout << "\r      " << ci << "/" << n_edges;
            ci++;
        }
    }
    std::cout << "\n";
    g.Vertex_map = vertices;
    g.Edges = grid;
    std::cout << "   Number of vertices: " << g.Vertex_map.size() << "\n";
    std::cout << "   Number of edges: " << grid.size() << "\n";

    for (std::map<string, Layer>::iterator it = Layers.begin(); it != Layers.end(); ++it) {
        it->second.g = g;
    }

    std::pair<std::set<int>, std::set<int>> XY(X, Y);
    return XY;
}


void Circuit::add_zero_edges_to_components(Set_Pair XY){
    std::cout << "Adding zero edges:\n";
    for (std::map<string, Layer>::iterator it = Layers.begin(); it != Layers.end(); ++it) {
        std::cout << "   " << it->first << ":\n";
        it->second.add_zero_edges_to_components(XY);
    }
}

void Circuit::convert_to_boost() {
    int i = 1, ne, n;
    std::cout << "Converting to boost graph\n";
    for (std::map<string, Layer>::iterator it = Layers.begin(); it != Layers.end(); ++it) {
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
            /* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Comentário importante
             * CONTINUAR AQUI
             *
             * O código até terminar esse laço ta demorando no total 8.63 minutos pro case1
             *
             * Usar try catch pra tentar inserir, ao inves de procurar pela bagaça com o find().
             * Testar pra ver se não da erro que nem no erase() do set.
             * Esse laço é o que mais ta demorando.
             *
             *
             * find(): O(log(Q(P)))
             * P = 4000
             * Q(P) = 16000000 ~= 1.6 * 10^7
             * Usando a função ~= 2 * Q(P)
             *
             * 2 * 16000000 * log(16000000) = 230531839 ~= 2.3 * 10^8
             *
             * qua, 25 de out, 03:44
             * <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
             */
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



void remove_collided_points_with_obstacles() {
    // Fazer o mesmo esquema de encontrar as arestas de peso 0, só que com
    // a lista de Obstacle.

    

}















//
