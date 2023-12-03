#include "common.hpp"
#include <cstring>
#include <vector>
#include <string>
#include <algorithm>

struct Draw
{
    int red = 0;
    int blue = 0;
    int green = 0;

    Draw(int red, int blue, int green);
    Draw(const std::string line);
};

Draw::Draw(const std::string line)
{   
    for (auto word : split(line, ",")){
        auto atomicelements = split(word, " ");
        if (atomicelements[1] == "green"){
            green += std::stoi(atomicelements[0]);
        } else if (atomicelements[1] == "blue"){
            blue += std::stoi(atomicelements[0]);
        } else if (atomicelements[1] == "red"){
            red += std::stoi(atomicelements[0]);
        }
    }
}

Draw::Draw(int arg_red, int arg_blue, int arg_green){
    red = arg_red;
    blue = arg_blue;
    green = arg_green;
}

Draw operator+(const Draw &a, const Draw &b)
{
    return Draw{
        (std::max)(a.red, b.red),
        (std::max)(a.blue, b.blue),
        (std::max)(a.green, b.green)};
}

struct Game
{
    int id;
    int total_red;
    int total_blue;
    int total_green;
    bool is_doable;
    std::vector<Draw> draw;

    Game(std::string line);
};

// Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
Game::Game(std::string line)
{
    size_t i1 = 0;
    size_t i2 = 0;
    i1 = line.find("Game ", 0) + std::string{"Game "}.size();
    i2 = line.find(':', i1);
    id = std::stoi(line.substr(i1, i2 - i1));
    std::cout << "Id : [" << id << "]" << std::endl; //<< id << std::endl;
    i1 = i2 + 1;
    std::cout << "[" << line[i1 - 1] << line[i1] << line[i1 + 1] << "]" << std::endl;
    Draw total_cubes{0,0,0};
    for (auto argument : split(line.substr(i1, std::string::npos), ";")){
        total_cubes = total_cubes + Draw{argument};
    }
    std::cout << "total_cubes = { blue : "<<total_cubes.blue<<"; green : "<<total_cubes.green<<"; red : "<<total_cubes.red << " } ";
    std::cout << "Is doable : "<< (total_cubes.blue <= 14 && total_cubes.green <= 13 && total_cubes.red <= 12) << std::endl;
    is_doable = (total_cubes.blue <= 14 && total_cubes.green <= 13 && total_cubes.red <= 12);

}

int day02part1(std::vector<std::string> lines)
{
    int res = 0;
    for (auto line : lines)
    {
        auto game = Game{line};
        res += game.is_doable ? game.id : 0;
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
            int res = day02part1(lines);
            std::cout << "Res 1 : " << res << std::endl;;
            // std::cout << "Res 1 : " << day01part1(lines) << std::endl;
        }
        // else if (std::strcmp(argv[1], "2") == 0)
        // {
        //     std::cout << "Res 2 : " << day01part2(lines) << std::endl;
        // }
    }
}