#include <iostream>
using namespace std;

class Layer {
    int g;  // Grafo

    public:
        void move_obstacles_points();
        void add_zero_edges_to_components();
        void remove_collided_points_with_obstacles();
        void draw();
};
