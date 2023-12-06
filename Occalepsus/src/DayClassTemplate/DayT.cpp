#include "DayT.h"

day_t DayT::run() {
	auto input = readInputFromFile(getDayInputPath());
	parseInput(input);

	return part1();
}

day_t DayT::part1() {
	int res = 0;

	return res;
}

day_t DayT::part2() {
	int res = 0;

	return res;
}

void DayT::parseInput(std::vector<std::string> const& input) {
	for (auto const& line : input) {
		// Do something
	}
}
