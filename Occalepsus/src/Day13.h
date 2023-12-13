#pragma once

#include "util/DayInterface.h"

#include <bitset>
#include <array>

using day_t = int;

constexpr int max_width = 20;

class Day13 : public DayInterface<day_t>
{
public:
	Day13() : DayInterface(R"(C:\Users\jujuj\Documents\Projets informatique\AdventOfCode2023\input\InputDay13.txt)") {};
	~Day13() override = default;

	day_t run() override;

private:
	struct Rock {
		int width{ 0 };
		int height{ 0 };
		std::array<std::bitset<max_width>, max_width> horizontal;
		std::array<std::bitset<max_width>, max_width> vertical;
	};

	std::vector<Rock> rocks;

	day_t part1();
	day_t part2();
	void parseInput(std::vector<std::string> const& input);
	bool checkSym(Rock const& rock, bool dirVert, int axis) const;
	bool checkSymDiff(Rock const& rock, bool dirVert, int axis) const;
};
