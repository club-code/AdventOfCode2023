#pragma once

#include "util/DayInterface.h"

using day_t = long long;

class Day11 : public DayInterface<day_t>
{
public:
	Day11() : DayInterface(R"(C:\Users\jujuj\Documents\Projets informatique\AdventOfCode2023\input\InputDay11.txt)") {};
	~Day11() override = default;

	day_t run() override;

private:
	struct Galaxy {
		int id;
		day_t x;
		day_t y;

		Galaxy(int id, day_t x, day_t y) : id(id), x(x), y(y) {};
	};
	std::vector<Galaxy> galaxies;

	day_t part1_2();
	void parseInput(std::vector<std::string> const& input, int separation = 2);
};
