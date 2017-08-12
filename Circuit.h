#include <iostream>
using namespace std;

class Circuit {
    int ViaCost, Spacing, N_MetalLayers, N_RoutedShapes, N_RoutedVias, N_Obstacles;
    int g;          // Grafo
    int Boundary;   // Retângulo

    public:
        void input_to_objects();
        void move_obstacles_points();
        void generate_hanan_grid();
        void add_zero_edges_to_components();
        void remove_collided_points_with_obstacles();
        void connect_all_components();
        void remove_one_degree_vertices();
        void remove_zero_edges();
        void generate_output();
        void draw();
};
