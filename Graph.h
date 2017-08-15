#include <vector>
#include <array>

using namespace std;

typedef array<int, 3> Vertex;

typedef struct edge{
    Vertex u;
    Vertex v;
    int w;
} Edge;


class Graph{
    vector<Vertex> Vertex_list;
    vector<Edge> Edge_list;

    public:
        void add_edge(Vertex, Vertex, int);
        void add_vertex(Vertex);
        vector<Vertex> vertex_set();
};
