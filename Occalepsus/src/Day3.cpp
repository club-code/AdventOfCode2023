#include "Day3.h"

int Day3::run() {
	auto input = readInputFromFile(getDayInputPath());

	return part2(input);
}

int Day3::part1(std::vector<std::string> const& input) {
	parseInput(input);

	int res = 0;

	// A symbol iterator for the zone
	auto zoneIt{symbols.begin() };

	for (auto const& number : numbers) {
		// Incrementing till we reach the row above the number
		while (zoneIt != symbols.end() && zoneIt->row < number.row - 1) {
			zoneIt++;
		}

		// Create a temp iterator, and increment it till we reach the row below the number (so that we are sure to have all the symbols in the zone)
		auto symIt{ zoneIt };
		while (symIt != symbols.end() && symIt->row <= number.row + 1) {
			if (symIt->col >= number.colStart - 1 && symIt->col <= number.colEnd + 1) {
				res += number.value;
				break;
			}
			symIt++;
		}
	}

	return res;
}

int Day3::part2(std::vector<std::string> const& input) {
	parseInput(input);

	// A symbol iterator for the zone
	auto zoneIt{ symbols.begin() };

	for (auto const& number : numbers) {
		// Incrementing till we reach the row above the number
		while (zoneIt != symbols.end() && zoneIt->row < number.row - 1) {
			zoneIt++;
		}

		// Create a temp iterator, and increment it till we reach the row below the number (so that we are sure to have all the symbols in the zone)
		auto symIt{ zoneIt };
		while (symIt != symbols.end() && symIt->row <= number.row + 1) {
			if (symIt->col >= number.colStart - 1 && symIt->col <= number.colEnd + 1) {
				symIt->adj++;
				symIt->ratio *= number.value;
				break;
			}
			symIt++;
		}
	}

	int res = 0;
	for (auto const& symbol : symbols) {
		if (symbol.symbol == '*' && symbol.adj == 2) {
			std::cout << "Found symbol " << symbol.symbol << " at " << symbol.row << ", " << symbol.col << " with ratio " << symbol.ratio << std::endl;
			res += symbol.ratio;
		}
	}

	return res;
}

void Day3::parseInput(std::vector<std::string> const& input) {
	numbers.clear();
	symbols.clear();

	Number tempNumber{ 0, 0, 0, 0 };
	
	int row{ 0 };
	int col{ 0 };
	for (auto const& line : input) {
		for (auto c : line) {
			if (c >= '0' && c <= '9') {
				if (tempNumber.value != 0) {
					tempNumber.value *= 10;
					tempNumber.value += c - '0';
				}
				else {
					tempNumber.value = c - '0';
					tempNumber.row = row;
					tempNumber.colStart = col;
				}
			}
			else {
				if (tempNumber.value != 0) {
					tempNumber.colEnd = col - 1;
					std::cout << "Found number " << tempNumber.value << " at " << tempNumber.row << ", " << tempNumber.colStart << std::endl;

					numbers.push_back(tempNumber);
					tempNumber = { 0, 0, 0, 0 };
				}

				if (c != '.') {
					symbols.push_back({ c, row, col, 0, 1 });
				}
			}

			col++;
		}

		if (tempNumber.value != 0) {
			tempNumber.colEnd = col - 1;
			std::cout << "Found number " << tempNumber.value << " at " << tempNumber.row << ", " << tempNumber.colStart << std::endl;

			numbers.push_back(tempNumber);
			tempNumber = { 0, 0, 0, 0 };
		}

		row++;
		col = 0;
	}
}
