// #pragma once
// #include <string>
// #include <vector>

// std::vector<std::string> getlines(std::string path);

#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "common.hpp"

std::vector<std::string> getlines(std::string path)
{
    std::fstream inputFile;
    inputFile.open(path, std::ios::in);
    if (!inputFile.is_open()){
        inputFile.close();
        std::cerr << "Could not open the file "<<path<<std::endl;
        throw std::invalid_argument("Could not open the file "+path);
    }
    std::string line;
    std::vector<std::string> res;
    while (std::getline(inputFile, line)){
        res.push_back(line.substr(0, line.find('\r')));
    }
    return res;
}