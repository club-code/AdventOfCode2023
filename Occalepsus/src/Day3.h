#pragma once

#include "util/DayInterface.h"

class Day3 : public DayInterface<int>
{
public:
	Day3() : DayInterface(R"(C:\Users\jujuj\Documents\Projets informatique\AdventOfCode2023\input\InputDay3.txt)") {};
	~Day3() override = default;

	int run() override;

private:
	struct Number {
		int value;
		int row;
		int colStart;
		int colEnd;
	};

	struct Symbol {
		char symbol;
		int row;
		int col;
		int adj;
		int ratio;
	};

	std::vector<Number> numbers;
	std::vector<Symbol> symbols;

	int part1(std::vector<std::string> const& input);
	int part2(std::vector<std::string> const& input);

	void parseInput(std::vector<std::string> const& input);
};
