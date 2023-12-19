#include "Day18.h"

#include <memory>
#include <utility>
#include <queue>

day_t Day18::run() {
	auto input = readInputFromFile(getDayInputPath());
	parseInput(input, true);

	return part2();
}

day_t Day18::part1() const {
	std::unique_ptr<Map> map{ std::make_unique<Map>() };

	int x{ map_size / 2 };
	int y{ map_size / 2 };

	int xMin{ x };
	int xMax{ x };
	int yMin{ y };
	int yMax{ y };

	for (auto const& instruction : instructions) {
		if (!step(*map, x, y, instruction)) {
			std::cout << "Map too small\n";
			exit(1);
		}

		if (x < xMin) {
			xMin = x;
		}
		if (x > xMax) {
			xMax = x;
		}
		if (y < yMin) {
			yMin = y;
		}
		if (y > yMax) {
			yMax = y;
		}
	}

	printMap(*map, xMin, xMax, yMin, yMax);

	digAround(*map, map_size / 2 + 1, map_size / 2 + 1);

	printMap(*map, xMin, xMax, yMin, yMax);

	day_t res{ 0 };

	for (y = 0; y < map_size; ++y) {
		for (x = 0; x < map_size; ++x) {
			if ((*map)[x][y]) {
				++res;
			}
		}
	}

	return res;
}

// 1072888051 too low

day_t Day18::part2() const {
	day_t res{ 0 };
	day_t offset{ 0 };

	day_t x{ 0 };
	day_t y{ 0 };

	// Triangle formula: https://en.wikipedia.org/wiki/Shoelace_formula#Triangle_formula
	for (auto it{ instructions.begin() }; it + 1 != instructions.end(); it++) {
		day_t xi{ x };
		day_t yi{ y };

		offset += step(x, y, *it);

		res += xi * y - x * yi;
	}

	res = res < 0 ? -res : res;

	return (res >> 1) + offset + 1;
}

void Day18::parseInput(std::vector<std::string> const& input, bool corr) {
	for (auto const& line : input) {
		Direction dir;
		if (!corr) {
			switch (line[0]) {
			case 'U':
				dir = Direction::North;
				break;
			case 'R':
				dir = Direction::East;
				break;
			case 'D':
				dir = Direction::South;
				break;
			case 'L':
				dir = Direction::West;
				break;
			default:
				exit(1);
			}
		}
		else {
			switch (*(line.rbegin() + 1) - '0') {
			case 0:
				dir = Direction::East;
				break;
			case 1:
				dir = Direction::South;
				break;
			case 2:
				dir = Direction::West;
				break;
			case 3:
				dir = Direction::North;
				break;
			default:
				exit(1);
			}
		}

		if (!corr) {
			if (line[3] == '0') {
				instructions.emplace_back(dir, 10);
			}
			else {
				instructions.emplace_back(dir, line[2] - '0');
			}
		}
		else {
			auto start{ line.find('#') + 1 };
			instructions.emplace_back(dir, std::stoi(line.substr(start, 5), nullptr, 16));
		}
	}
}

bool Day18::step(Map& map, int& x, int& y, Instruction const& instruction) const {
	switch (instruction.dir) {
	case Direction::North:
		if (x - instruction.dist < 0) {
			return false;
		}

		for (int i{ 0 }; i < instruction.dist; ++i) {
			map[x][y] = true;
			--x;
		}
		break;
	case Direction::East:
		if (y + instruction.dist >= map_size) {
			return false;
		}

		for (int i{ 0 }; i < instruction.dist; ++i) {
			map[x][y] = true;
			++y;
		}
		break;
	case Direction::South:
		if (x + instruction.dist >= map_size) {
			return false;
		}

		for (int i{ 0 }; i < instruction.dist; ++i) {
			map[x][y] = true;
			++x;
		}
		break;
	case Direction::West:
		if (y - instruction.dist < 0) {
			return false;
		}

		for (int i{ 0 }; i < instruction.dist; ++i) {
			map[x][y] = true;
			--y;
		}
		break;
	}
	return true;
}

day_t Day18::step(day_t& x, day_t& y, Instruction const& instruction) const {
	switch (instruction.dir) {
	case Direction::North:
		x -= instruction.dist;
		return 0;
	case Direction::East:
		y += instruction.dist;
		return 0;
	case Direction::South:
		x += instruction.dist;
		return instruction.dist;
	case Direction::West:
		y -= instruction.dist;
		return instruction.dist;
	}
	return true;
}

void Day18::digAround(Map& map, int x, int y) const {
	std::queue<std::pair<int, int>> toDig;
	toDig.emplace(x, y);

	while (!toDig.empty()) {
		auto const& [digX, digY] = toDig.front();

		if (!map[digX][digY]) {
			map[digX][digY] = true;

			if (digX > 0) {
				toDig.emplace(digX - 1, digY);
			}
			if (digX < map_size - 1) {
				toDig.emplace(digX + 1, digY);
			}
			if (digY > 0) {
				toDig.emplace(digX, digY - 1);
			}
			if (digY < map_size - 1) {
				toDig.emplace(digX, digY + 1);
			}
		}

		toDig.pop();
	}
}

void Day18::printMap(Map const& map, int xMin, int xMax, int yMin, int yMax) const {
	for (int x{ xMin }; x <= xMax; ++x) {
		for (int y{ yMin }; y <= yMax; ++y) {
			if (x == map_size / 2 && y == map_size / 2) {
				std::cout << '+';
				continue;
			}
			std::cout << (map[x][y] ? '#' : '.');
		}
		std::cout << '\n';
	}
}
