#include "Day10.h"

day_t Day10::run() {
	auto input = readInputFromFile(getDayInputPath());
	parseInput(input);

	return part1();
}

day_t Day10::part1() {
	day_t res{ 0 };

	auto pos{ startingPos };
	auto lastDir{ Dir::North }; // Hardcoded for the input
	do {
		// Get the next direction
		if (pipes[pos.second][pos.first].first != getOppositeDir(lastDir)) {
			lastDir = pipes[pos.second][pos.first].first;
		}
		else {
			lastDir = pipes[pos.second][pos.first].second;
		}

		// Move
		switch (lastDir) {
			case Dir::North:
				pos.second--;
				break;
			case Dir::East:
				pos.first++;
				break;
			case Dir::South:
				pos.second++;
				break;
			case Dir::West:
				pos.first--;
				break;
			default:
				std::cout << "Error: Undefined direction" << std::endl;
				throw std::exception("Out of grid");
		}
		res++;

	} while (startingPos != pos);

	return (int)ceil((double)(res) / 2);
}

day_t Day10::part2() {
	day_t res{ 0 };

	auto pos{ startingPos };
	auto lastDir{ Dir::North }; // Hardcoded for the input
	do {
		// Get the next direction
		if (pipes[pos.second][pos.first].first != getOppositeDir(lastDir)) {
			lastDir = pipes[pos.second][pos.first].first;
		}
		else {
			lastDir = pipes[pos.second][pos.first].second;
		}

		// Move
		switch (lastDir) {
		case Dir::North:
			pos.second--;
			break;
		case Dir::East:
			pos.first++;
			break;
		case Dir::South:
			pos.second++;
			break;
		case Dir::West:
			pos.first--;
			break;
		default:
			std::cout << "Error: Undefined direction" << std::endl;
			throw std::exception("Out of grid");
		}
		res++;

	} while (startingPos != pos);

	return (int)ceil((double)(res) / 2);
}

void Day10::parseInput(std::vector<std::string> const& input) {
	int x{ 0 };
	int y{ 0 };

	for (auto const& line : input) {
		std::vector<std::pair<Dir, Dir>> linePipes;
		std::vector<Status> lineMap;
		for (auto c : line) {
			switch (c) {
			case '|':
				linePipes.emplace_back(Dir::North, Dir::South);
				break;
			case '-':
				linePipes.emplace_back(Dir::East, Dir::West);
				break;
			case 'F':
				linePipes.emplace_back(Dir::East, Dir::South);
				break;
			case '7':
				linePipes.emplace_back(Dir::West, Dir::South);
				break;
			case 'J':
				linePipes.emplace_back(Dir::West, Dir::North);
				break;
			case 'L':
				linePipes.emplace_back(Dir::East, Dir::North);
				break;
			case 'S':
				startingPos = { x, y };
				[[fallthrough]];
			case '.':
				linePipes.emplace_back(Dir::Undefined, Dir::Undefined);
				break;
			default:
				break;
			}
			lineMap.push_back(Status::Unknown);
			x++;
		}
		pipes.push_back(linePipes);
		map.push_back(lineMap);
		x = 0;
		y++;
	}

	setupStartingPos();
}

void Day10::setupStartingPos() {
	Dir dirA{ Dir::Undefined };
	Dir dirB{ Dir::Undefined };
	if (startingPos.first < pipes[startingPos.second].size() + 1 && (pipes[startingPos.second][startingPos.first + 1].first == Dir::West || pipes[startingPos.second][startingPos.first + 1].second == Dir::West)) {
		dirA = Dir::East;
	}
	if (startingPos.second < pipes.size() + 1 && (pipes[startingPos.second + 1][startingPos.first].first == Dir::North || pipes[startingPos.second + 1][startingPos.first].second == Dir::North)) {
		if (dirA == Dir::Undefined) {
			dirA = Dir::South;
		}
		else {
			dirB = Dir::South;
		}
	}
	if (dirB == Dir::Undefined && startingPos.first > 0 && (pipes[startingPos.second][startingPos.first - 1].first == Dir::East || pipes[startingPos.second][startingPos.first - 1].second == Dir::East)) {
		if (dirA == Dir::Undefined) {
			dirA = Dir::West;
		}
		else {
			dirB = Dir::West;
		}
	}
	if (dirB == Dir::Undefined && startingPos.second > 0 && (pipes[startingPos.second - 1][startingPos.first].first == Dir::South || pipes[startingPos.second - 1][startingPos.first].second == Dir::South)) {
		dirB = Dir::North;
	}
	pipes[startingPos.second][startingPos.first] = { dirA, dirB };
}

Day10::Dir Day10::getOppositeDir(Dir dir) {
	if (dir == Dir::Undefined) {
		return Dir::Undefined;
	}
	return (Dir)(((int)dir + 2) % 4);
}
