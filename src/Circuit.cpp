#include <fstream>
#include <string>
#include <iostream>
#include "Circuit.h"
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>


void Circuit::draw(){
    for (std::map<string, Layer>::iterator it = Layers.begin(); it != Layers.end(); ++it) {
        std::cout << it->first << ":\n";
        std::cout << "Shapes:\n";
        it->second.print_shapes(0);
        std::cout << "Obstacles:\n";
        it->second.print_shapes(1);
        std::cout << "Vias:\n";
        it->second.print_vias();
        std::cout << "\n";
    }
}


void Circuit::input_to_objects(string case_path){
    std::ifstream fs(case_path);
    std::string line,  one, two, three, four;
    std::vector<std::string> input;
    std::vector<std::string> strs;

    while (std::getline(fs, line))
        input.push_back(line);


    boost::split(strs, input.at(0), boost::is_any_of("\t "));
    this->ViaCost = boost::lexical_cast<int>(strs.at(2));

    boost::split(strs, input.at(1), boost::is_any_of("\t "));
    this->Spacing = boost::lexical_cast<int>(strs.at(2));

    boost::split(strs, input.at(3), boost::is_any_of("\t "));
    this->N_MetalLayers = boost::lexical_cast<int>(strs.at(2));

    boost::split(strs, input.at(4), boost::is_any_of("\t "));
    this->N_RoutedShapes = boost::lexical_cast<int>(strs.at(2));

    boost::split(strs, input.at(5), boost::is_any_of("\t "));
    this->N_RoutedVias = boost::lexical_cast<int>(strs.at(2));

    boost::split(strs, input.at(6), boost::is_any_of("\t "));
    this->N_Obstacles = boost::lexical_cast<int>(strs.at(2));


    //  Cria as camadas no circuito (ainda vazias)
    for (int i = 1; i <= this->N_MetalLayers; i++) {
        Layer l;
        this->Layers["M" + std::to_string(i)] = l;
    }


    //  Instanciação dos objetos das Layers
    for (int i = 0; i < N_RoutedShapes; i++) {
        boost::split(strs, input.at(i + 7), boost::is_any_of("\t "));
        Layers[strs.at(1)].add_shape(strs);
    }

    int j = N_RoutedShapes + 7;
    for (int i = 0; i < N_RoutedVias; i++) {
        boost::split(strs, input.at(j + i), boost::is_any_of("\t "));
        Layers["M" + strs.at(1).substr(1, 1)].add_via(strs);

        std::string adj_layer = std::to_string(boost::lexical_cast<int>(strs.at(1).substr(1, 1)) + 1);
        Layers["M" + adj_layer].add_via(strs);
    }


    j = N_RoutedVias + N_RoutedShapes + 7;
    for (int i = 0; i < N_Obstacles; i++) {
        boost::split(strs, input.at(j + i), boost::is_any_of("\t "));
        Layers[strs.at(1)].add_shape(strs);

    }

    fs.close();
}
