#pragma once

#include "util/DayInterface.h"

using day_t = int;

class DayT : public DayInterface<day_t>
{
public:
	DayT() : DayInterface(R"(C:\Users\jujuj\Documents\Projets informatique\AdventOfCode2023\input\InputDayT.txt)") {};
	~DayT() override = default;

	day_t run() override;

private:
	day_t part1();
	day_t part2();
	void parseInput(std::vector<std::string> const& input);
};
