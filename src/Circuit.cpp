#include <fstream>
#include <string>
#include <iostream>
#include "Circuit.h"
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>


void Circuit::draw(){
    std::cout << ViaCost << "\n"
              << Spacing << "\n"
              << N_MetalLayers << "\n"
              << N_RoutedShapes << "\n"
              << N_RoutedVias << "\n"
              << N_Obstacles << "\n";

    for (std::map<string, Layer>::iterator it = Layers.begin(); it != Layers.end(); ++it) {
        std::cout << it->first << '\n';
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


    for (int i = 0; i < N_RoutedShapes; i++) {
        //input.at(i + 7);
        boost::split(strs, input.at(i + 7), boost::is_any_of("\t "));
        Layers[strs.at(1)].add_shape(strs);
    }


    //int j = N_RoutedShapes + 7;
    for (int i = 0; i < N_RoutedVias; i++) {
        //input.at(j + i);
    }


    //j = N_RoutedVias + N_RoutedShapes + 7;
    for (int i = 0; i < N_Obstacles; i++) {
        //input.at(j + i);
    }


    fs.close();
}
