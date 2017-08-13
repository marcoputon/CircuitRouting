#include <iostream>
#include "Graph.h"


using namespace boost;
using namespace std;

int main(){
    UndirectedGraph g;

    add_edge (0, 1, 8, g);
    add_edge (0, 3, 18, g);
    add_edge (1, 2, 20, g);
    add_edge (0, 1, 2, g);
    add_edge (1, 3, 7, g);
    add_edge (1, 4, 1, g);
    add_edge (4, 5, 6, g);
    add_edge (2, 5, 7, g);

    pair<edge_iterator, edge_iterator> ei = edges(g);

    cout << "Number of edges = " << num_edges(g) << "\n";
    cout << "Edge list:\n";

    for (edge_iterator it = ei.first; it != ei.second; ++it){
        cout << *it << endl;
    }

    cout << endl;

    return 0;
 }
