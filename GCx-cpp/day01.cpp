// #pragma once
#include "common.hpp"
#include <iostream>
#include <string>
#include <cstring>
#include <map>

int getDigitsFromLine(std::string line)
{
    auto begin = line.begin();
    auto end = line.end() - 1;

    while (!('0' <= *begin && *begin <= '9'))
    {
        begin++;
    }

    int res_begin = 10 * ((*begin) - '0');

    while (!('0' <= *end && *end <= '9'))
    {
        end--;
    }
    int res_end = ((*end) - '0');
    std::cout << "For line " + line + " : " << res_begin + res_end << std::endl;
    return res_begin + res_end;
}

int day01part1(std::vector<std::string> lines)
{
    int res = 0;
    for (auto line : lines)
    {
        res += getDigitsFromLine(line);
    }
    return res;
}

int getLettersFromLine(std::string line)
{
    std::map<std::string, int> words{
        {"one", 1},
        {"two", 2},
        {"three", 3},
        {"four", 4},
        {"five", 5},
        {"six", 6},
        {"seven", 7},
        {"eight", 8},
        {"nine", 9}};

    size_t begin = 0;
    size_t end = line.size() - 1;

    int word_begin = 0;

    std::cout << "In line " << line << " ";

    while (word_begin == 0 && begin < line.size())
    {
        if (('1' <= line[begin] && line[begin] <= '9'))
        {
            word_begin = (int)(line[begin] - '0');
            std::cout << word_begin;
        }
        else
        {
            for (auto word : words)
            {
                if (begin + word.first.size() < line.size() && line.substr(begin, word.first.size()) == word.first)
                {
                    word_begin = word.second;
                    std::cout << line.substr(begin, word.first.size()) << " ";
                }
            }
        }
        begin++;
    }
    std::cout << " ";
    int word_end = 0;
    while (word_end == 0 && end >= 0)
    {
        if (('1' <= line[end] && line[end] <= '9'))
        {
            word_end = (int)(line[end] - '0');
            std::cout << word_end << std::endl;
        }
        else
        {
            for (auto word : words)
            {
                if (end + word.first.size() <= line.size() && line.substr(end, word.first.size()) == word.first)
                {
                    word_end = word.second;
                    std::cout << line.substr(end, word.first.size()) << std::endl;
                }
            }
        }
        end--;
    }

    return (10 * word_begin) + word_end;
}

int day01part2(std::vector<std::string> lines)
{
    int res = 0;
    for (auto line : lines)
    {
        res += getLettersFromLine(line);
    }
    return res;
}

int main(int argc, char **argv)
{
    std::vector<std::string> lines;
    if (argc == 3)
    {
        lines = getlines(argv[2]);
        if (std::strcmp(argv[1], "1") == 0)
        {
            std::cout << "Res 1 : " << day01part1(lines) << std::endl;
        }
        else if (std::strcmp(argv[1], "2") == 0)
        {
            std::cout << "Res 2 : " << day01part2(lines) << std::endl;
        }
    }
}