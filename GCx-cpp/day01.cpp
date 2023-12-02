// #pragma once
#include "common.hpp"
#include <iostream>
#include <string>
#include <cstring>

int getDigitsFromLine(std::string line)
{
    auto begin = line.begin();
    auto end = line.end()-1;
    
    while (!( '0' <= *begin && *begin <= '9'))
    {
        begin++;
    }

    int res_begin = 10*((*begin)-'0');

    while(!('0' <= *end && *end <= '9'))
    {
        end--;
    }
    int res_end = ((*end) - '0');
    std::cout << "For line "+line+" : "<<res_begin+res_end<<std::endl;
    return res_begin+res_end;
}

int day01part1(std::vector<std::string> lines){
    int res = 0;
    for (auto line : lines){
        res += getDigitsFromLine(line);
    }
    return res;
}

int main (int argc, char** argv)
{
    std::vector<std::string> lines;
    if (argc == 3){
        lines = getlines(argv[2]);
        if (std::strcmp(argv[1], "1") == 0)
        {
            std::cout << "Res 1 : "<<day01part1(lines) << std::endl;
        }
    }
}