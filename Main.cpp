#include <iostream>
#include <list>
#include <vector>
#include <array>

using namespace std;

typedef array<int, 3> Vertex;

typedef struct edge{
    Vertex u;
    Vertex v;
} Edge;



int main(){

    Edge e;
    e.u = {1, 2, 3};
    e.v = {5, 6, 7};

    cout << e.u[0] << "\n";

    return 0;
}
