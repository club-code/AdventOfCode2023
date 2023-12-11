#pragma once

#include "util/DayInterface.h"

using day_t = int;

class Day10 : public DayInterface<day_t>
{
public:
	Day10() : DayInterface(R"(C:\Users\jujuj\Documents\Projets informatique\AdventOfCode2023\input\InputDay10.txt)") {};
	~Day10() override = default;

	day_t run() override;

private:
	enum Dir {
		Undefined = -1,
		North,
		East,
		South,
		West
	};
	enum Status {
		Unknown = -1,
		Loop,
		Outside,
		Inside
	};

	std::vector<std::vector<std::pair<Dir, Dir>>> pipes;
	std::vector<std::vector<Status>> map;
	std::pair<int, int> startingPos;

	day_t part1();
	day_t part2();
	void parseInput(std::vector<std::string> const& input);
	void setupStartingPos();
	Dir getOppositeDir(Dir dir);
};
