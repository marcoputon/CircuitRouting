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


void Circuit::generate_hanan_grid(bool gen_img) {
    std::cout << "Generating hanan grid\n";

    std::set<int> X;
    std::set<int> Y;
    std::set<int> Z;

    std::vector<Vertex> vertices;
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

    this->XY = Set_Pair(X, Y);
    g.g = Graph(X.size() * Y.size() * Z.size());

    int v_num = 0;
    //Vertices
    for (std::set<int>::iterator x = X.begin(); x != X.end(); ++x) {
        for (std::set<int>::iterator y = Y.begin(); y != Y.end(); ++y) {
            for (std::set<int>::iterator z = Z.begin(); z != Z.end(); ++z) {
                bool flag = false;
                for (Shape o : Layers[*z].Obstacles) {
                    if (point_collide_rect({*x,*y,*z}, o)) {
                        flag = true;
                        break;
                    }
                }
                if (!flag) {
                    V vd = v_num;
                    v_num++;
                    rev_map[{*x,*y,*z}] = vd;
                }
            }
        }
    }

    //Arestas
    for (std::set<int>::iterator x = X.begin(); x != X.end(); ++x) {
        for (std::set<int>::iterator y = Y.begin(); y != Y.end(); ++y) {
            for (std::set<int>::iterator z = Z.begin(); z != Z.end(); ++z) {
                std::set<int>::iterator xp = x;
                std::set<int>::iterator yp = y;
                std::set<int>::iterator zp = z;

                ++xp;
                ++yp;
                ++zp;

                if (xp != X.end()){
                    if ((rev_map.find({*x,*y,*z}) != rev_map.end()) && (rev_map.find({*xp,*y,*z}) != rev_map.end()))
                        boost::add_edge(rev_map[{*x,*y,*z}], rev_map[{*xp,*y,*z}], euclidian_dist({*x,*y,*z}, {*xp,*y,*z}), g.g);
                }
                if (yp != Y.end()){
                    if ((rev_map.find({*x,*y,*z}) != rev_map.end()) && (rev_map.find({*x,*yp,*z}) != rev_map.end()))
                        boost::add_edge(rev_map[{*x,*y,*z}], rev_map[{*x,*yp,*z}], euclidian_dist({*x,*y,*z}, {*x,*yp,*z}), g.g);
                }
                if (zp != Z.end()){
                    if ((rev_map.find({*x,*y,*z}) != rev_map.end()) && (rev_map.find({*x,*y,*zp}) != rev_map.end()))
                        boost::add_edge(rev_map[{*x,*y,*z}], rev_map[{*x,*y,*zp}], euclidian_dist({*x,*y,*z}, {*x,*y,*zp}), g.g);
                }
            }
        }
    }
    if (gen_img)
        to_dot(g.g);
}


void Circuit::spanning_tree(bool gen_img) {
    std::vector <E> spanning_tree;
    boost::kruskal_minimum_spanning_tree(this->g.g, std::back_inserter(spanning_tree));

    spanning = Graph(boost::num_vertices(this->g.g));

    for (E e : spanning_tree) {
        V vs = source(e, this->g.g);
        V vt = target(e, this->g.g);
        int w = boost::get(edge_weight, this->g.g, e);

        boost::add_edge(vs, vt, w, spanning);
    }
    //to_dot(spanning);


    if (gen_img){
        std::cout << "Generatig MST\n";
        std::ofstream myfile;
        myfile.open("spanning.dot");
        myfile << "graph {\n";

        for (std::vector<E>::iterator ei = spanning_tree.begin(); ei != spanning_tree.end(); ++ei) {
            myfile << source(*ei, this->g.g) << " -- " << target(*ei, this->g.g) << "\n";
        }

        myfile << "}";
        myfile.close();
    }

}


void Circuit::close_component(Vertex A, Vertex B, Vertex C) {
    std::set<int> X, Y;

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


    // Adiciona as arestas verticais
    for (std::set<int>::iterator it_x = X.begin(); it_x != X.end(); ++it_x) {
        for (std::set<int>::iterator it_y = Y.begin(); it_y != Y.end(); ++it_y) {
            std::set<int>::iterator it_yp = it_y;
            ++it_yp;
            if (it_yp == Y.end())
            break;

            Vertex u = {*it_x, *it_y, A[2]};
            Vertex v = {*it_x, *it_yp, A[2]};

            boost::add_edge(this->rev_map[u], this->rev_map[v], 0, this->spanning);
        }
    }

    // Adiciona as arestas horizontais
    for (std::set<int>::iterator it_y = Y.begin(); it_y != Y.end(); ++it_y) {
        for (std::set<int, bool>::iterator it_x = X.begin(); it_x != X.end(); ++it_x) {
            std::set<int, bool>::iterator it_xp = it_x;
            ++it_xp;
            if (it_xp == X.end())
            break;

            Vertex u = {*it_x, *it_y, A[2]};
            Vertex v = {*it_xp, *it_y, A[2]};

            boost::add_edge(this->rev_map[u], this->rev_map[v], 0, this->spanning);
        }
    }
}


void Circuit::close_components_cycles() {
    std::cout << "close_components_cycles\n";

    for (std::map<int, Layer>::iterator it = Layers.begin(); it != Layers.end(); ++it) {
        for (Shape c : it->second.Components) {
            close_component(c.A, c.B, c.C);
        }
    }
}


void Circuit::remove_one_degree_vertices() {
    std::cout << "remove_one_degree_vertices\n";
    bool flag = true;
    std::vector<bool> visited(num_vertices(this->spanning), false);


    while (flag) {
        flag = false;
        for (std::pair<VI, VI> vi = boost::vertices(this->spanning); vi.first != vi.second; ++vi.first) {
            if (!visited[*vi.first] && boost::degree(*vi.first, this->spanning) < 2) {
                flag = true;
                visited[*vi.first] = true;
                boost::clear_vertex(*vi.first, this->spanning);
                break;
            }
        }
    }

    to_dot(this->spanning);
}


















//
