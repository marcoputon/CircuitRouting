#include "Shape.h"

/*
A ------- B
|         |
|         |
|         |
D ------- C
*/



bool Shape::point_collision(Vertex v) {
    return v[2] == A[2] && ((A[0] <= v[0]) && (C[0] >= v[0])) && ((A[1] >= v[1]) && (C[1] <= v[1]));
}


bool Shape::collide_edge_with_vertex(Vertex v) {
    return v[2] == A[2] && (
        ( ((A[0] < v[0]) && (C[0] > v[0])) && ((A[1] == v[1]) && (C[1] <= v[1]))) ||
        ( ((A[1] < v[1]) && (C[1] > v[1])) && ((A[0] == v[0]) && (C[0] <= v[0])))
    );

}


bool Shape::collide_with_edge(Edge e) {
    return point_collision(e.u) && point_collision(e.v);
}
