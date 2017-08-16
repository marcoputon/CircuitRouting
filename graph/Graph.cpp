#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <iostream>
#include <vector>
#include <array>
#include <utility>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/adjacency_iterator.hpp>


typedef std::array<int, 3> Vertex;


typedef boost::property<boost::edge_weight_t, int> EdgeWeightProperty;
typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS, boost::no_property, EdgeWeightProperty> UndirectedGraph;
typedef boost::graph_traits<UndirectedGraph>::edge_iterator edge_iterator;


struct Node {
    Vertex v;
    std::string identifier;

    Node(const std::string & i): identifier(i) {}
    Node(): identifier("default") {}
};

typedef boost::adjacency_list<
    boost::setS,
    boost::vecS,
    boost::undirectedS,
    Node, int
> G;



struct Graph {
    G graph;

    int add_vertex(const std::string & name) {
        return boost::add_vertex(Node(name), graph);
    }

    int new_vertex() {
        return boost::add_vertex(graph);
    }

    void add_edge(int u, int v, int w) {
        boost::add_edge(u, v, w, graph);
    }
};


int main(){
    Graph g;
    g.add_vertex("1");
    g.add_vertex("1");

    G::vertex_descriptor a = g.new_vertex();
    G::vertex_descriptor b = g.new_vertex();

    g.add_edge(a, b, 5);

    


    return 0;
}
