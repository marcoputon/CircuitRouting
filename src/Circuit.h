#include <iostream>
#include <string>
#include "Layer.h"


using namespace std;

struct Circuit {
    int ViaCost, Spacing, N_MetalLayers, N_RoutedShapes, N_RoutedVias, N_Obstacles;
    G g;
    Graph spanning;
    int Boundary; // Retângulo
    std::map<int, Layer> Layers;
    Set_Pair XY;
    std::map<Vertex, V> rev_map;
    std::map<V, Vertex> ver_map;


    void input_to_objects(string);
    void move_obstacles_points();
    void generate_hanan_grid(bool);
    void spanning_tree(bool);
    void remove_one_degree_vertices();
    void close_component(Vertex, Vertex, Vertex);
    void close_components_cycles();
    void components_edges(vector<nEdge>*);
    void components_edges2(vector<nEdge>*);
    void componentEdges(Vertex, Vertex, Vertex, vector<nEdge>*);

    void remove_collision_with_obstacles(Set_Pair);
    void convert_to_boost();
    void connect_all_components();
    void add_zero_edges_to_components(Set_Pair);
    void draw();
    void generate_output();
    void remove_zero_edges();

};
