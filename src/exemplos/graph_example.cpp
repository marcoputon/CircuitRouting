#include "Graph.h"
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

    graph.add_vertex_to_map(u0);
    graph.add_vertex_to_map(u1);
    graph.add_vertex_to_map(u2);
    graph.add_vertex_to_map(u3);
    graph.add_vertex_to_map(u4);
    graph.print_Vertex_map();
    std::cout << "\n";

    graph.add_edge_to_vec(u0, u1, 2);
    graph.add_edge_to_vec(u1, u2, 2);
    graph.print_edges();


    return 0;
}
