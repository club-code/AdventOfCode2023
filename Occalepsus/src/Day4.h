#pragma once

#include "util/DayInterface.h"

class Day4 : public DayInterface<int>
{
public:
	Day4() : DayInterface(R"(C:\Users\jujuj\Documents\Projets informatique\AdventOfCode2023\input\InputDay4.txt)") {};
	~Day4() override = default;

	int run() override;

private:
	struct Card {
		int score;
		std::vector<int> winning;
		std::vector<int> scratched;
		int copies{ 1 };
	};
	std::vector<Card> cards;

	int part1(std::vector<std::string> const& input);
	int part2(std::vector<std::string> const& input);
	void parseInput(std::vector<std::string> const& input);
};
