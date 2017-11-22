#define GRAPH_H 1

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <map>
#include <tr1/unordered_map>

using namespace boost;


typedef std::pair<std::set<int>, std::set<int>> Set_Pair;
typedef std::pair<std::vector<int>, std::vector<int>> Vector_Pair;
typedef std::array<int, 3> Vertex;

struct Edge {
    Vertex u;
    Vertex v;
    int w;

    bool operator< (const Edge&) const;
    bool operator== (const Edge&) const;
};

namespace std {
    template<>
    class hash<Edge> {
        public:
            size_t operator()(const Edge &s) const {
                //size_t h1 = std::hash<std::string>()(s.first_name);
                //size_t h2 = std::hash<std::string>()(s.last_name);
                return 0;//h1 ^ ( h2 << 1 );
            }
    };
}

// Grafo é uma lista de adjacencia com lista de vértices, arestas, não dirigido e com peso nas arestas
typedef adjacency_list <vecS, setS, undirectedS, no_property, property <edge_weight_t, int>> Graph;

// Bagulhos pra iterar nas arestas e vértices
typedef graph_traits <Graph>::edge_descriptor E;
typedef graph_traits <Graph>::edge_iterator EI;
typedef graph_traits <Graph>::vertex_descriptor V;
typedef graph_traits <Graph>::vertex_iterator VI;
typedef property_map<Graph, vertex_index_t>::type IndexMap;


//  Estrutura do Grafo
struct G {
    Graph g;
    IndexMap index;

    //  Trabalhar com essas listas antes de usar o grafo
    std::map<Vertex, V> Vertex_map; // I have no idea how the vertices got here (but they are)
    std::set <Edge> Edges;


    G();

    void map_to_graph();

    void add_vertex_to_map(Vertex);
    void add_vertex(Vertex);
    void remove_vertex(Vertex);
    void remove_vertex_from_map(Vertex);
    void print_vertices();
    void print_Vertex_map();

    void add_edge_to_sec(Vertex, Vertex, int);
    void add_edge(V, V, int);
    void remove_edge_from_map(Edge);
    void print_edges();
    void print_edges_set();
};


void to_dot(Graph);
void print_edges(std::vector<E>, G);
void print_edge(Edge e);
int euclidian_dist(Vertex, Vertex);
