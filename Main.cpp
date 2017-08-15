#include <iostream>
#include "Graph.h"


int main(){
    Graph g;

    g.add_vertex({1, 2, 3});
    g.add_vertex({3, 0, -1});

    for(Vertex v : g.vertex_set()){
        std::cout << "(" << v[0] << ", " << v[1] << ", " <<  v[2] << ")\n";
    }

    return 0;
}
