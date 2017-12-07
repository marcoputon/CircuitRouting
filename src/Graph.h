#define GRAPH_H 1

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <map>
#include <tr1/unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

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
                return 0;
            }
    };
}

// Grafo é uma lista de adjacencia com lista de vértices, arestas, não dirigido e com peso nas arestas
typedef adjacency_list <vecS, vecS, undirectedS, no_property, property <edge_weight_t, int>> Graph;

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



struct UF {
    vector<int> rank;
    vector<int> root;

    UF(int n): rank(n, 0), root(n) {
        for(int i = 0; i < n; ++i) root[i] = i;
    }

    int Find(int x) {
        if (root[x] != x) {
            root[x] = Find(root[x]);
        }
        return root[x];
    }

    void Union(int x, int y) {
        if (rank[root[x]] > rank[root[y]]) {
            root[root[y]] = root[x];
        }
        else if (rank[root[x]] < rank[root[y]]) {
            root[root[x]] = root[y];
        }
        else {
            root[root[y]] = root[x];
            rank[x]++;
        }
    }
};


struct nEdge {
    int u, v, w;

    nEdge(int u_, int v_, int w_):u(u_), v(v_), w(w_) {}

    friend bool operator<(const nEdge & a, const nEdge & b) {
        return a.w < b.w;
    }
};


struct MST {
    vector<nEdge> edges;
    vector<nEdge> result;

    int n;
    int sum;

    MST(int n_, Graph* g): n(n_), sum(0) {
        EI ei, ei_end;

        for (boost::tie(ei, ei_end) = boost::edges(*g); ei != ei_end; ++ei) {
            edges.emplace_back(source(*ei, *g), target(*ei, *g), boost::get(edge_weight, *g, *ei));
        }
    }

    vector<nEdge> compute(bool dir, vector<nEdge> components) {
        UF uf(n);
        if (dir) sort(edges.rbegin(), edges.rend());
        else     sort(edges.begin(),  edges.end());

        result.clear();
        sum = 0;

        /* Insere as arestas dos componentes no conjunto solução para não gerar
        ciclos com vértices de camadas adjacentes */
        for (nEdge c : components) {
            result.push_back(c);
            uf.Union(c.u, c.v);
            sum += c.w;
        }

        for(const nEdge & e : edges) {
            if(uf.Find(e.u) != uf.Find(e.v)) {
                result.push_back(e);
                uf.Union(e.u, e.v);
                sum += e.w;
            }
        }
        return result;
    }
};
