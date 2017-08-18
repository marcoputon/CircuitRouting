#include <iostream>
#include "Graph.h"


int main(){
    Graph g;

    Vertex u = {1, 2, 3};
    Vertex v = {1, 2, 3};
/*
    if (u == v) std::cout << "igual\n";
    else std::cout << "diferente\n";
*/
    g.add_edge(u, v, 3);
    g.add_edge(u, v, 1);
    g.add_edge(u, v, 5);
    g.add_edge(u, v, 2);
    g.add_edge(u, v, 6);
    g.add_edge(u, v, 7);

    /*
    for(Vertex v : g.vertex_set()){
        std::cout << "(" << v[0] << ", " << v[1] << ", " <<  v[2] << ")\n";
    }
    */
    Graph t;
    t = g.kruskal();

    for(Edge e : t.edge_set()){
        std::cout << "(" << e.u[0] << ", " << e.u[1] << ", " <<  e.u[2] << ") - " << "(" << e.v[0] << ", " << e.v[1] << ", " <<  e.v[2] << ") - " << e.w << "\n";
    }

    return 0;
}
