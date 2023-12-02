#pragma once

#include "util/DayInterface.h"

class DayT : public DayInterface<int>
{
public:
	DayT() : DayInterface(R"(C:\Users\jujuj\Documents\Projets informatique\AdventOfCode2023\input\InputDayT.txt)") {};
	~DayT() override = default;

	int run() override;

private:
	int part1(std::vector<std::string> const& input) const;
	int part2(std::vector<std::string> const& input) const;
};
