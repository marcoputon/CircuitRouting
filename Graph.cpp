#include "Graph.h"

void Graph::add_edge(int x, int y, int w){
    boost::add_edge(x, y, w, g);
}
