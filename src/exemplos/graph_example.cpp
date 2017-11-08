#include "../Graph.h"
#include "iostream"

void draw_edge(V label, Vertex v) {
    std::cout << label << " [pos=\"" v[0] << "," << v[1] << "," << v[2] << "\"]";
}

int main() {
    G graph;;

    Vertex u0 = {0, 0, 0};
    Vertex u1 = {1, 1, 1};
    Vertex u2 = {2, 2, 2};
    Vertex u3 = {3, 3, 3};
    Vertex u4 = {4, 4, 4};

    graph.add_vertex(u0);
    graph.add_vertex(u1);
    graph.add_vertex(u2);
    graph.add_vertex(u3);
    graph.add_vertex(u4);

    graph.add_edge(graph.Vertex_map[u0], graph.Vertex_map[u1], 2);
    graph.add_edge(graph.Vertex_map[u1], graph.Vertex_map[u2], 2);


    std::cout << "graph {";

    // 	A [pos = "0,0!"]
    for (std::pair<EI, EI> ei = boost::edges(graph.g); ei.first != ei.second; ++ei.first) {
        std::cout << *ei.first << "\n";

        for () {
            
        }
    }

    std::cout << "}";
    return 0;
}
