#include "../Graph.h"
#include "iostream"

int main() {
    G graph;
    std::vector <E> spanning_tree;
/*
*/
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
    graph.print_Vertex_map();
    std::cout << "\n";

    graph.add_edge_to_sec(u0, u1, 2);
    graph.add_edge_to_sec(u1, u2, 2);
    graph.print_edges();

    std::cout << "\n\n\n\n";


    graph.remove_vertex(u2);
    graph.print_Vertex_map();


    return 0;
}
