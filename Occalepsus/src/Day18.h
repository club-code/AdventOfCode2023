#pragma once

#include "util/DayInterface.h"

#include <array>
#include <vector>

using day_t = long long;

class Day18 : public DayInterface<day_t>
{
public:
	constexpr static int map_size{ 500 };

	Day18() : DayInterface(R"(C:\Users\jujuj\Documents\Projets informatique\AdventOfCode2023\input\InputDay18.txt)") {};
	~Day18() override = default;

	day_t run() override;

private:
	using Map = std::array<std::array<bool, map_size>, map_size>;

	enum Direction {
		North,
		East,
		South,
		West
	};

	struct Instruction {
		Direction dir;
		int dist;

		Instruction(Direction dir, int dist) : dir(dir), dist(dist) {};
	};

	std::vector<Instruction> instructions;

	day_t part1() const;
	day_t part2() const;
	void parseInput(std::vector<std::string> const& input, bool corr = false);
	bool step(Map& map, int& x, int& y, Instruction const& instr) const;
	day_t step(day_t& x, day_t& y, Instruction const& instr) const;
	void digAround(Map& map, int x, int y) const;
	void printMap(Map const& map, int xMin, int xMax, int yMin, int yMax) const;
};
