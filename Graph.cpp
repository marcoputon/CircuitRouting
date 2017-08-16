#include <algorithm>
#include <iostream>
#include "Graph.h"

/*
    for(Edge e : ve){
        std::cout << "(" << e.u[0] << ", " << e.u[1] << ", " <<  e.u[2] << ") - " << "(" << e.v[0] << ", " << e.v[1] << ", " <<  e.v[2] << ") - " << e.w << "\n";
    }
*/

void Graph::add_vertex(Vertex u){
    Vertex_list.push_back(u);
}

void Graph::add_edge(Vertex u, Vertex v, int w){
    Edge e;
    e.u = u;
    e.v = v;
    e.w = w;
    Edge_list.push_back(e);
}

vector<Vertex> Graph::vertex_set(){ return Vertex_list; }

vector<Edge> Graph::edge_set(){ return Edge_list; }




Graph Graph::kruskal(){
    Graph g;

    g.Vertex_list = this->vertex_set();
    vector<Edge> ve = this->edge_set();

    std::sort(ve.begin(), ve.end(), less_than_key());

    

    return g;
}
