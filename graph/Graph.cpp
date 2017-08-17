#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <iostream>
#include <map>

using namespace boost;


// Vértice é um array de tamanho 3
typedef std::array<int, 3> Vertex;

// Grafo é uma lista de adjacencia com lista de vértices, arestas, não dirigido e com peso nas arestas
typedef adjacency_list <vecS, vecS, undirectedS, no_property, property <edge_weight_t, int>> Graph;

// Bagulhos pra iterar nas arestas e vértices
typedef graph_traits <Graph>::edge_descriptor E;
typedef graph_traits <Graph>::vertex_descriptor V;


struct G {
    Graph g;
    std::map<Vertex, V> Vertex_map;

    //  Adiciona o vértice no mapa de vértices tendo como chave o vertex_descriptor
    void add_vertex(Vertex v){
        V vd = boost::add_vertex(g);
        Vertex_map[v] = vd;
    };

    //  Acho que vai bugar se adicionar aresta com vertices não contidos no Grafo
    //  porque não vai adicionar no Vertex_map os novos vértices.
    void add_edge(Vertex u, Vertex v, int w){
        boost::add_edge(Vertex_map[u], Vertex_map[v], w, g);
    };
};




int main() {
    G graph;
    Vertex u1 = {1, 2, 1};
    Vertex u2 = {3, 5, 4};
    Vertex u3 = {6, 6, 6};

    graph.add_vertex(u1);
    graph.add_vertex(u2);
    graph.add_vertex(u3);

    graph.add_edge(u1, u2, 3);
    graph.add_edge(u1, u3, 2);
    graph.add_edge(u2, u3, 1);

    return 0;
}
