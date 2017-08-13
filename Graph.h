#include <boost/graph/adjacency_list.hpp>

typedef boost::property<boost::edge_weight_t, int> EdgeWeightProperty;
typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS, boost::no_property, EdgeWeightProperty> UndirectedGraph;
typedef boost::graph_traits<UndirectedGraph>::edge_iterator edge_iterator;

class Graph{
    UndirectedGraph g;

    public:
        void add_edge(int, int, int);
};
