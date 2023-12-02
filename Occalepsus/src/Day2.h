#pragma once

#include "util/DayInterface.h"

#include <regex>

class Day2 : public DayInterface<int>
{
public:
	Day2() : DayInterface(R"(C:\Users\jujuj\Documents\Projets informatique\AdventOfCode2023\input\InputDay2.txt)") {};
	~Day2() override = default;

	int run() override;

private:
	struct ColorSet {
		int r{ 0 };
		int g{ 0 };
		int b{ 0 };
	};
	const ColorSet targetColor{ 12, 13, 14 };

	int part1(std::vector<std::string> const& input) const;
	int part2(std::vector<std::string> const& input) const;
	std::vector<Day2::ColorSet> parseLine(std::string const& line) const;
};
