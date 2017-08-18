#include "Graph.h"
#include <iostream>


void G::add_vertex(Vertex v){
    V vd = boost::add_vertex(g);
    Vertex_map[v] = vd;
    std::cout << vd << " - ";
};

void G::add_edge(Vertex u, Vertex v, int w){
    boost::add_edge(Vertex_map[u], Vertex_map[v], w, g);
};


void print_edges(std::vector <E> spanning_tree, G graph){
    for (std::vector <E>::iterator ei = spanning_tree.begin(); ei != spanning_tree.end(); ++ei) {
        std::cout << source(*ei, graph.g) << " <--> " << target(*ei, graph.g)
                  << " with weight of " << get(edge_weight, graph.g, *ei)
                  << std::endl;
    }
}
