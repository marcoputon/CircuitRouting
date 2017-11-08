#include "Graph.h"
#include <iostream>
#include <math.h>
#include <utility>
#include <string>
#include <fstream>


G::G(int s):g(s), index(get(vertex_index, g)) {
}


bool Edge::operator< (const Edge& e) const {
    return (u < e.u) || (u == e.u && v < e.v);
}


bool Edge::operator== (const Edge& x) const {
    return (u == x.u && v == x.v) || (u == x.v && v == x.u);
}


//  Modidicar para (não sei ainda)
void G::add_edge(V u, V v, int w) {
    boost::add_edge(u, v, w, g);
}

/*
graph {
	A [pos = "0,0"]
	B [pos = "10,10"]

	A -- B
}

*/


void G::to_dot() {
    EI ei, ei_end;
    std::string out;
    std::ofstream myfile;
    myfile.open("teste.dot");
    myfile << "graph {\n";


    for (boost::tie(ei, ei_end) = boost::edges(g); ei != ei_end; ++ei) {
        myfile << source(*ei, g) << " -- " << target(*ei, g) << "\n";
    }

    myfile << "}";
    myfile.close();
    std::cout << out;
}


//  PRINT ----------------------------------------------------------------------------------------------------------------

void G::print_vertices() {
    std::pair<VI, VI> vi;

    for (vi = vertices(this->g); vi.first != vi.second; ++vi.first) {
        V vd = *vi.first;
        std::cout << index[vd] << std::endl;
    }
}


void G::print_edges(){
    for (Edge e : this->Edges){
        std::cout << "(" << e.u[0] << ", " << e.u[1] << ", " << e.u[2] << ") - ("
                         << e.v[0] << ", " << e.v[1] << ", " << e.v[2] << ") - "
                         << e.w << "\n";
    }
}

void G::print_Vertex_map() {
    for (std::map<Vertex,V>::iterator it = Vertex_map.begin(); it != Vertex_map.end(); ++it) {
        std::cout << "(" << it->first[0] << ", " << it->first[1] << ", " << it->first[2] << ") => " << it->second << '\n';
    }
}
/*
*/

void print_edges(std::vector <E> spanning_tree, G graph) {
    for (std::vector <E>::iterator ei = spanning_tree.begin(); ei != spanning_tree.end(); ++ei) {
        std::cout << source(*ei, graph.g) << " <--> " << target(*ei, graph.g)
                  << " with weight of " << get(edge_weight, graph.g, *ei)
                  << std::endl;
    }
}

void print_edge(Edge e) {
    std::cout << "(" << e.u[0] << ", " << e.u[1] << ", " << e.u[2] << ") - ("
                     << e.v[0] << ", " << e.v[1] << ", " << e.v[2] << ") - "
                     << e.w << "\n";
}


int euclidian_dist(Vertex u, Vertex v) {
    return (sqrt(pow(u[0] - v[0], 2) + pow(u[1] - v[1], 2) + pow(u[2] - v[2], 2)));
}

void G::print_edges_set() {
    int i = 0;
    for (std::pair<EI, EI> ei = boost::edges(g); ei.first != ei.second; ++ei.first) {
        std::cout << *ei.first << "\n";
        i++;
    }
    std::cout << "numero de arestas: " << i << "\n";
}
