#include "Graph.h"

int main() {
    G graph;
    std::vector <E> spanning_tree;

    Vertex u1 = {1, 2, 1};
    Vertex u2 = {3, 5, 4};
    Vertex u3 = {6, 6, 6};
    Vertex u4 = {6, 6, 7};

    graph.add_vertex(u1);
    graph.add_vertex(u2);
    graph.add_vertex(u3);
    graph.add_vertex(u4);

    graph.add_edge(u1, u2, 1);
    graph.add_edge(u2, u3, 2);
    graph.add_edge(u3, u4, 5);
    graph.add_edge(u4, u1, 4);
    graph.add_edge(u1, u3, 3);

    kruskal_minimum_spanning_tree(graph.g, std::back_inserter(spanning_tree));

    std::cout << "\n";
    print_edges(spanning_tree, graph);


    return 0;
}
