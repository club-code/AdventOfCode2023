#include "Day11.h"

day_t Day11::run() {
	auto input = readInputFromFile(getDayInputPath());
	parseInput(input, 1000000);

	return part1_2();
}

day_t Day11::part1_2() {
	day_t res{ 0 };

	for (auto it1{ galaxies.begin() }; it1 != galaxies.end(); it1++) {
		for (auto it2{ it1 + 1 }; it2 != galaxies.end(); it2++) {
			res += std::abs(it1->x - it2->x) + std::abs(it1->y - it2->y);
		}
	}

	return res;
}

void Day11::parseInput(std::vector<std::string> const& input, int separation) {
	std::vector<bool> foundCol{ input.front().size(), false, std::allocator<bool>() };
	
	int id{ 0 };
	day_t x{ 0 };
	day_t y{ 0 };

	// Iterate a first time to find the columns with at least one #
	for (auto const& line : input) {
		for (auto c : line) {
			if (c == '#') {
				foundCol[x] = true;
			}
			x++;
		}
		x = 0;
	}

	x = 0;
	// Iterate a second time to find the galaxies
	for (auto const& line : input) {
		// Setup the holes
		auto it{ foundCol.begin() };
		bool foundLine{ false };
		for (auto c : line) {
			// If the column is empty, we add one to the x coordinate
			if (!*it) {
				x += separation - 1;
			}
			// If there is a galaxy, we add it to the vector
			if (c == '#') {
				galaxies.emplace_back(id, x, y);
				id++;
				foundLine = true;
			}
			x++;
			it++;
		}
		// If there is no galaxy on the line, we add one to the y coordinate
		if (!foundLine) {
			y += separation - 1;
		}
		x = 0;
		y++;
	}
}
