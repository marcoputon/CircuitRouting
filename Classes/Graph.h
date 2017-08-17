#include <vector>
#include <array>

using namespace std;


typedef array<int, 3> Vertex;


typedef struct edge{
    Vertex u;
    Vertex v;
    int w;
} Edge;


struct less_than_key{
    inline bool operator() (const Edge& struct1, const Edge& struct2){
        return (struct1.w < struct2.w);
    }
};


class Graph{
    vector<Vertex> Vertex_list;
    vector<Edge> Edge_list;

    public:
        void add_edge(Vertex, Vertex, int);
        void add_vertex(Vertex);
        vector<Vertex> vertex_set();
        vector<Edge> edge_set();

        Graph kruskal();
};
