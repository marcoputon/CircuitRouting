#include "Graph.h"
#include <iostream>
#include <math.h>


G::G(){
    index = get(vertex_index, g);
}


bool Edge::operator< (const Edge& x) const {
    return u[0] != x.u[0] || u[1] != x.u[1] || u[2] != x.u[2] ||
           v[0] != x.v[0] || v[1] != x.v[1] || v[2] != x.v[2];
}

bool Edge::operator== (const Edge& x) const {
    return (u[0] == x.u[0] && u[1] == x.u[1] && u[2] == x.u[2] &&
           v[0] == x.v[0] && v[1] == x.v[1] && v[2] == x.v[2]) ||
           (u[0] == x.v[0] && u[1] == x.v[1] && u[2] == x.v[2] &&
            v[0] == x.u[0] && v[1] == x.u[1] && v[2] == x.u[2]);
}


//  -1 para vértices não inicializados
void G::add_vertex_to_map(Vertex v) {
    this->Vertex_map[v] = -1;
}

void G::add_vertex(Vertex v) {
    V vi = boost::add_vertex(this->g);
    this->Vertex_map[v] = vi;
}


void G::add_edge_to_vec(Vertex u, Vertex v, int w) {
    Edge e;
        e.u = u;
        e.v = v;
        e.w = w;
    this->Edges.push_back(e);
}


//  Modificar para remover apenas do mapa
void G::remove_vertex_from_map(Vertex v) {
    this->Vertex_map.erase(v);
}

void G::remove_vertex(Vertex v) {
    boost::remove_vertex(Vertex_map[v], this->g);
    this->Vertex_map.erase(v);
}



//  Modidicar para (não sei ainda)
void G::add_edge(Vertex u, Vertex v, int w) {
    boost::add_edge(Vertex_map[u], Vertex_map[v], w, g);
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
