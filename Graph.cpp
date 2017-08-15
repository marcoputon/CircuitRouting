#include "Graph.h"


void Graph::add_vertex(Vertex u){
    Vertex_list.insert(u);
}

void Graph::add_edge(Vertex u, Vertex v, int w){
    Edge e;
    e.u = u;
    e.v = v;
    e.w = w;
    Edge_list.insert(e);
}
