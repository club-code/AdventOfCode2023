#pragma once

#include "util/DayInterface.h"

#include <array>
#include <queue>
#include <list>

using day_t = int;

class Day15 : public DayInterface<day_t>
{
public:
	Day15() : DayInterface(R"(C:\Users\jujuj\Documents\Projets informatique\AdventOfCode2023\input\InputDay15.txt)") {};
	~Day15() override = default;

	day_t run() override;

private:
	std::vector<std::queue<char>> inputQueues;

	struct Step {
		std::string label;
		int length;
		
		Step() = default;
		Step(std::string const& label, int length) : label(label), length(length) {};
	};
	std::vector<Step> steps;

	std::array<std::list<Step>, 256> map;

	day_t part1();
	day_t part2();
	void parseInput(std::vector<std::string> const& input);
	void hashAppendChar(char c, day_t& hash) const;
	int hashString(std::string_view const& str) const;
};
