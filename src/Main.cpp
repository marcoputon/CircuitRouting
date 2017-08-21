#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Graph.h"


int main(){
    Graph g;

    std::ifstream fs("../cases/case0");
    std::string line;
    std::vector<std::string> input;

    while (std::getline(fs, line))
        input.push_back(line);


    std::cout << input.at(0) << std::endl;

    //  comparation between unsigned and signed integer
    for (int i = 7; i < int(input.size()); i++) {
        std::cout << input.at(i) << "\n";
    }


    fs.close();

    return 0;
}
