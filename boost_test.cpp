#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <iostream>
#include <fstream>

int main(){
    using namespace boost;
    typedef adjacency_list <vecS, vecS, undirectedS, no_property, property <edge_weight_t, int>> Graph;
    typedef graph_traits <Graph>::edge_descriptor Edge;
    typedef graph_traits <Graph>::vertex_descriptor Vertex;
    typedef std::pair<int, int> E;


}
