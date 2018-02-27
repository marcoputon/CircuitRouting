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

    std::cout << "  Getting coordinates\n";
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

    std::cout << "  Creating vertices\n";
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
                    ver_map[vd] = {*x,*y,*z};
                }
            }
        }
    }

    std::cout << "  Creating edges\n";
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
    if (gen_img) to_dot(g.g);
}


void Circuit::components_edges(vector<nEdge>* edges) {
    EI ei, ei_end;
    for (boost::tie(ei, ei_end) = boost::edges(this->g.g); ei != ei_end; ++ei) {
        Edge ne;
        ne.u = ver_map[source(*ei, this->g.g)];
        ne.v = ver_map[target(*ei, this->g.g)];

        bool flag = false;
        for (std::map<int, Layer>::iterator it = Layers.begin(); it != Layers.end(); ++it) {
            for (Shape c : it->second.Components) {
                if (c.collide_with_edge(ne)) {
                    flag = true;
                    break;
                }
            }
            if (flag) break;
        }

        if (flag) {
            edges->emplace_back(source(*ei, this->g.g), target(*ei, this->g.g), boost::get(edge_weight, this->g.g, *ei));
        }
    }
}


void Circuit::componentEdges(Vertex A, Vertex B, Vertex C, vector<nEdge>* edges) {
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
            if (it_yp == Y.end()) break;

            Vertex u = {*it_x, *it_y, A[2]};
            Vertex v = {*it_x, *it_yp, A[2]};
            nEdge ne = nEdge(this->rev_map[u], this->rev_map[v], euclidian_dist(u, v));
            if(std::find(edges->begin(), edges->end(), ne) == edges->end())
                edges->push_back(ne);
        }
    }

    // Adiciona as arestas horizontais
    for (std::set<int>::iterator it_y = Y.begin(); it_y != Y.end(); ++it_y) {
        for (std::set<int, bool>::iterator it_x = X.begin(); it_x != X.end(); ++it_x) {
            std::set<int, bool>::iterator it_xp = it_x;
            ++it_xp;
            if (it_xp == X.end()) break;

            Vertex u = {*it_x, *it_y, A[2]};
            Vertex v = {*it_xp, *it_y, A[2]};

            nEdge ne = nEdge(this->rev_map[u], this->rev_map[v], euclidian_dist(u, v));
            if(std::find(edges->begin(), edges->end(), ne) == edges->end())
                edges->push_back(ne);
        }
    }
}


void Circuit::components_edges2(vector<nEdge>* edges) {
    for (std::map<int, Layer>::iterator it = Layers.begin(); it != Layers.end(); ++it) {
        for (Shape c : it->second.Components) {
            componentEdges(c.A, c.B, c.C, edges);
        }
    }
}


void Circuit::spanning_tree(bool gen_img) {
    std::cout << "Spanning tree\n";
    std::vector <E> spanning_tree;
    int num_edges = boost::num_edges(this->g.g);
    MST mst(num_edges, &this->g.g);
    vector<nEdge> components;
    vector<nEdge> components2;

    std::cout << "  Getting component edges\n";
    components_edges(&components);
    /*components_edges2(&components2);
    std::cout << components.size() << " - " << components2.size() << "\n";


    for (int i = 0; i < components.size(); i++) {
        std::cout << components[i].u  << "<->" << components[i].v << ": " << components[i].w << " / " << components2[i].u  << "<->" << components2[i].v << ": " << components2[i].w << "\n";
    }
    */
    std::cout << "  Finding spanning tree\n";
    vector<nEdge> kruskal = mst.compute(1, components);
    std::cout << "  Done finding spanning tree\n";

    spanning = Graph(boost::num_vertices(this->g.g));

    for (nEdge e : kruskal) {
        boost::add_edge(e.u, e.v, e.w, spanning);
    }
    //to_dot(spanning);


    if (gen_img){
        EI ei, ei_end;
        std::string out;
        std::ofstream myfile;
        myfile.open("out/teste.dot");
        myfile << "graph {\n";

        for (boost::tie(ei, ei_end) = boost::edges(this->spanning); ei != ei_end; ++ei) {
            Edge ne;
            ne.u = ver_map[source(*ei, this->spanning)];
            ne.v = ver_map[target(*ei, this->spanning)];

            bool flag = false;
            for (std::map<int, Layer>::iterator it = Layers.begin(); it != Layers.end(); ++it) {
                for (Shape c : it->second.Components) {
                    if (c.collide_with_edge(ne)) {
                        flag = true;
                        break;
                    }
                }
                if (flag) break;
            }

            if (!flag) {
                myfile << source(*ei, this->spanning) << " -- " << target(*ei, this->spanning) << "\n";
            }
            else {
                myfile << source(*ei, this->spanning) << " -- " << target(*ei, this->spanning) << " [color=\"red\"]\n";
            }
        }

        myfile << "}";
        myfile.close();
        std::cout << out;
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
            if (it_yp == Y.end()) break;

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
            if (it_xp == X.end()) break;

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


string v_string(Vertex v) {
    return string("(" + std::to_string(v[0]) + ", " + std::to_string(v[1]) + ", " + std::to_string(v[2]) + ")\n");
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
    //to_dot(this->spanning);

    EI ei, ei_end;
    std::ofstream myfile, result;
    myfile.open("out/grau1.dot");
    result.open("out/result.out");
    myfile << "graph {\n";

    for (boost::tie(ei, ei_end) = boost::edges(this->spanning); ei != ei_end; ++ei) {
        Edge ne;
        ne.u = ver_map[source(*ei, this->spanning)];
        ne.v = ver_map[target(*ei, this->spanning)];

        // VVV Isso tudo é pra colocar cor diferente nas arestas dos componentes VVV
        /* bool flag = false;
        for (std::map<int, Layer>::iterator it = Layers.begin(); it != Layers.end(); ++it) {
            for (Shape c : it->second.Components) {
                if (c.collide_with_edge(ne)) {
                    flag = true;
                    break;
                }
            }
            if (flag) break;
        }

        // RESULTADO
        if (!flag) {
        */
            myfile << source(*ei, this->spanning) << " -- " << target(*ei, this->spanning) << "\n";
            result << v_string(ver_map[source(*ei, this->spanning)]);
            result << v_string(ver_map[target(*ei, this->spanning)]);
            result << "\n";
        /*
        }
        // COMPONENTES
        else {
            myfile << source(*ei, this->spanning) << " -- " << target(*ei, this->spanning) << " [color=\"blue\"]\n";
        }
        // AAA Isso tudo é pra colocar cor diferente nas arestas dos componentes AAA
        */
    }
    myfile << "}";
    myfile.close();
}


















//
