#include <iostream>
#include "Shape.h"
#include "Via.h"
#include <vector>


using namespace std;

struct Layer {
    std::vector<Shape> Components;
    std::vector<Shape> Obstacles;
    std::vector<Via> Vias;


    void add_shape(std::vector<string>);
    void add_via(std::vector<string>);
    void move_obstacles_points();
    void add_zero_edges_to_components(Set_Pair);
    std::set<Vertex> find_collision_with_obstacles(Set_Pair);
    void set_third_coord(int);
    void draw();

    void print_shapes(bool);
    void print_vias();
};

std::set<Edge> interval (Set_Pair, Vertex, Vertex, Vertex); // XY, A, B, C

void print_v(Vertex);
