#include "Graph.h"
#include <iostream>


G::G(){
    index = get(vertex_index, g);
}


void G::add_vertex(Vertex v) {
    V vd = boost::add_vertex(g);
    Vertex_map[v] = vd;
}


void G::remove_vertex(Vertex v) {
    boost::remove_vertex(Vertex_map[v], g);
    Vertex_map.erase(v);
}


void G::add_edge(Vertex u, Vertex v, int w) {
    boost::add_edge(Vertex_map[u], Vertex_map[v], w, g);
}


void G::print_vertices() {
    std::pair<VI, VI> vi;

    for (vi = vertices(this->g); vi.first != vi.second; ++vi.first) {
        V vd = *vi.first;
        std::cout << index[vd] << std::endl;
    }
}


void G::print_Vertex_map() {
    for (std::map<Vertex,V>::iterator it = Vertex_map.begin(); it != Vertex_map.end(); ++it) {
        std::cout << "(" << it->first[0] << ", " << it->first[1] << ", " << it->first[2] << ") => " << it->second << '\n';
    }
}


void print_edges(std::vector <E> spanning_tree, G graph) {
    for (std::vector <E>::iterator ei = spanning_tree.begin(); ei != spanning_tree.end(); ++ei) {
        std::cout << source(*ei, graph.g) << " <--> " << target(*ei, graph.g)
                  << " with weight of " << get(edge_weight, graph.g, *ei)
                  << std::endl;
    }
}
