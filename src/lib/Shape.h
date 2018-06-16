#include <iostream>
#ifndef GRAPH_H
    #include "Graph.h"
#endif
using namespace std;

struct Shape {
    Vertex A;
    Vertex B;
    Vertex C;
    Vertex D;

    bool point_collision(Vertex);
    bool collide_with_edge(Edge);
    void draw();
};
