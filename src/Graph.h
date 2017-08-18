#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <map>
#include <tr1/unordered_map>

using namespace boost;


// Vértice é um array de tamanho 3
typedef std::array<int, 3> Vertex;


// Grafo é uma lista de adjacencia com lista de vértices, arestas, não dirigido e com peso nas arestas
typedef adjacency_list <vecS, vecS, undirectedS, no_property, property <edge_weight_t, int>> Graph;

// Bagulhos pra iterar nas arestas e vértices
typedef graph_traits <Graph>::edge_descriptor E;
typedef graph_traits <Graph>::vertex_descriptor V;


//  Estrutura do Grafo
struct G {
    Graph g;
    std::map<Vertex, V> Vertex_map;

    //  Adiciona o vértice no mapa de vértices tendo como chave o vertex_descriptor
    void add_vertex(Vertex);

    //  Acho que vai bugar se adicionar aresta com vertices não contidos no Grafo
    //  porque não vai adicionar no Vertex_map os novos vértices.
    void add_edge(Vertex, Vertex, int);
};


void print_edges(std::vector<E>, G);
