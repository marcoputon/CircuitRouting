#include <iostream>
#include "Shape.h"
#include "Via.h"
#include <vector>


using namespace std;

struct Layer {
    G g;  // Grafo
    std::vector<Shape> Components;
    std::vector<Shape> Obstacles;
    std::vector<Via> Vias;


    void add_shape(std::vector<string>);
    void add_via(std::vector<string>);
    void move_obstacles_points();
    void add_zero_edges_to_components();
    void remove_collided_points_with_obstacles();
    void set_third_coord(int);
    void draw();

    void print_shapes(bool);
    void print_vias();
};

void print_v(Vertex);
