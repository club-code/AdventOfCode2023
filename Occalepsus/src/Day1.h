#pragma once

#include "util/DayInterface.h"

class Day1 : public DayInterface<int>
{
public:
	Day1() : DayInterface(R"(C:\Users\jujuj\Documents\Projets informatique\AdventOfCode2023\input\InputDay1.txt)") {};
	~Day1() override = default;

	int run() override;

private:
	int part1(std::vector<std::string> const& input) const;
	int part2(std::vector<std::string> const& input) const;
	int findLine(std::string_view const& line) const;
	int findLine2(std::string_view const& line) const;
};
