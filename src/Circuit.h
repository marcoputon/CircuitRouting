#include <iostream>
#include <string>
#include "Layer.h"


using namespace std;

struct Circuit {
    int ViaCost, Spacing, N_MetalLayers, N_RoutedShapes, N_RoutedVias, N_Obstacles;
    G g; // Grafo
    int Boundary; // Retângulo
    std::map<int, Layer> Layers;


    void input_to_objects(string);
    void move_obstacles_points();
    void generate_hanan_grid();
    void add_zero_edges_to_components(Set_Pair);
    void convert_to_boost();
    void remove_collision_with_obstacles(Set_Pair);
    void connect_all_components();
    void remove_one_degree_vertices();
    void remove_zero_edges();
    void generate_output();
    void draw();
    void spanning_tree();
    void close_components_cycles();
};
