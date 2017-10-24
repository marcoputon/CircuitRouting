#include <iostream>
#include <set>
#include <array>
#include "../Graph.h"


Edge create (Vertex u, Vertex v, int w) {
    Edge new_e;
    new_e.u = u;
    new_e.v = v;
    new_e.w = w;
    return new_e;
}

int main () {
    std::set<Edge> edges;

    Vertex a = {1, 1, 1};
    Vertex b = {2, 2, 2};
    Vertex c = {3, 3, 3};
    Vertex d = {4, 4, 4};

    Edge e1 = create(a, b, 0);
    Edge e2 = create(a, c, 0);
    Edge e3 = create(c, d, 0);
    Edge e4 = create(b, a, 0);

    edges.insert(e1);
    edges.insert(e2);
    edges.insert(e3);
    edges.insert(e4);

    for (std::set<Edge>::iterator it = edges.begin(); it != edges.end(); ++it) {
        Edge e = *it;
        print_edge(e);
    }

    Edge ed = create(a, b, 2);

    if (edges.find(ed) != edges.end()) std::cout << "Achou\n";
    else std::cout << "Não achou\n";

    return 0;
}
