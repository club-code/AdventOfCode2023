#pragma once

#include "util/DayInterface.h"

using day_t = long long;

class Day6 : public DayInterface<day_t>
{
public:
	Day6() : DayInterface(R"(C:\Users\jujuj\Documents\Projets informatique\AdventOfCode2023\input\InputDay6.txt)") {};
	~Day6() override = default;

	day_t run() override;

private:
	struct Record {
		day_t time;
		day_t distance;
	};
	std::vector<Record> records;
	Record singleRecord{ 0, 0 };

	day_t part1() const;
	day_t part2() const;
	void parseInput(std::vector<std::string> const& input);
};
