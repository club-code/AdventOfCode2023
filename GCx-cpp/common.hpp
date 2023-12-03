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

std::vector<std::string> split(std::string line, std::string delimiter)
{
    std::vector<std::string> res{};
    size_t pos = 0;
    std::string token;
    while ((pos = line.find(delimiter))!= std::string::npos)
    {
        token = line.substr(0, pos);
        if (token.size()!=0){
            res.push_back(token);
        }
        line.erase(0, pos + delimiter.length());
    }
    token = line.substr(0, pos);
    if (token.size() != 0){
        res.push_back(token);
    }
    return res;
}