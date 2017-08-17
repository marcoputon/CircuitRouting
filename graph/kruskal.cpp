#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <iostream>
#include <fstream>

int main() {
    using namespace boost;
    typedef adjacency_list <vecS, vecS, undirectedS, no_property, property <edge_weight_t, int>> Graph;
    typedef graph_traits < Graph >::edge_descriptor Edge;
    typedef graph_traits < Graph >::vertex_descriptor V;

    Graph g;

    std::vector <Edge> spanning_tree;

    V v1 = add_vertex(g);
    V v2 = add_vertex(g);
    add_edge(v1, v2, 5, g);
    add_edge(v1, v2, 10, g);

    kruskal_minimum_spanning_tree(g, std::back_inserter(spanning_tree));

    std::cout << "Print the edges in the MST:" << std::endl;
    for (std::vector < Edge >::iterator ei = spanning_tree.begin(); ei != spanning_tree.end(); ++ei) {
        std::cout << source(*ei, g) << " <--> " << target(*ei, g)
                  << " with weight of " << get(edge_weight, g, *ei)
                  << std::endl;
    }

    return EXIT_SUCCESS;
}
