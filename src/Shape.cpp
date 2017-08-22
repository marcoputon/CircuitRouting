#include "Shape.h"


bool col_collision(Vertex u, Vertex v, Edge e) {
    Vertex Aux;

    // Mesmo Y
    if ((u[1] == v[1]) && (e.u[1] == e.v[1]) && (u[1] == e.u[1])) {
        if (u[0] > v[0]){
            Aux = v;
            v = u;
            u = Aux;
        }

        if (e.u[0] > e.v[0]){
            Aux = e.v;
            e.v = e.u;
            e.u = Aux;
        }

        if (e.u[0] >= u[0] && e.v[0] <= v[0]) {
            return true;
        }
    }
    // Mesmo X
    else if ((u[0] == v[0]) and (e.u[0] == e.v[0]) and (u[0] == e.u[0])) {
        if (u[1] > v[1]){
            Aux = v;
            v = u;
            u = Aux;
        }

        if (e.u[1] > e.v[1]){
            Aux = e.v;
            e.v = e.u;
            e.u = Aux;
        }

        if (e.u[1] >= u[1] && e.v[1] <= v[1]) {
            return true;
        }
    }
    return false;
}


bool Shape::collide_with_edge(Edge e) {
    if (col_collision(this->A, this->B, e) || col_collision(this->B, this->C, e)
    || col_collision(this->C, this->D, e) || col_collision(this->D, this->A, e)) {
        return true;
    }
    else
    return false;
}
