#include "Day13.h"

day_t Day13::run() {
	auto input = readInputFromFile(getDayInputPath());
	parseInput(input);

	return part2();
}

day_t Day13::part1() {
	day_t res{ 0 };

	for (auto const& rock : rocks) {
		for (int i{ 0 }; i < rock.width - 1; i++) {
			if (rock.vertical[i] == rock.vertical[i + 1] && checkSym(rock, true, i)) {
				res += i + 1;
				// std::cout << "Found vert sym at " << i + 1 << " (" << i + 1 << "), res = " << res << " for rock " << &rock << "\n";
				break;
			}
		}
		for (int i{ 0 }; i < rock.height - 1; i++) {
			if (rock.horizontal[i] == rock.horizontal[i + 1] && checkSym(rock, false, i)) {
				res += 100 * (i + 1);
				// std::cout << "Found horiz sym at " << i + 1 << " (" << 100 * (i + 1) << "), res = " << res << " for rock " << &rock << "\n";
				break;
			}
		}
	}

	return res;
}

day_t Day13::part2() {
	day_t res{ 0 };

	for (auto const& rock : rocks) {
		for (int i{ 0 }; i < rock.width - 1; i++) {
			if (checkSymDiff(rock, true, i)) {
				res += i + 1;
				std::cout << "Found vert sym at " << i + 1 << " (" << i + 1 << "), res = " << res << " for rock " << &rock << "\n";
				break;
			}
		}
		for (int i{ 0 }; i < rock.height - 1; i++) {
			if (checkSymDiff(rock, false, i)) {
				res += 100 * (i + 1);
				std::cout << "Found horiz sym at " << i + 1 << " (" << 100 * (i + 1) << "), res = " << res << " for rock " << &rock << "\n";
				break;
			}
		}
	}

	return res;
}

void Day13::parseInput(std::vector<std::string> const& input) {
	Rock newRock;
	int x{ 0 };
	int y{ 0 };
	for (auto const& line : input) {
		if (line.empty()) {
			newRock.height = y;
			y = 0;
			rocks.push_back(newRock);
			newRock = Rock();
			continue;
		}

		for (auto c : line) {
			if (c == '#') {
				newRock.horizontal[y].set(x);
				newRock.vertical[x].set(y);
			}
			x++;
		}

		if (newRock.width == 0) {
			newRock.width = x;
		}
		x = 0;
		y++;
	}
	newRock.height = y;
	rocks.push_back(newRock);
}

bool Day13::checkSym(Rock const& rock, bool dirVert, int axis) const {
	if (dirVert) {
		int i{ axis - 1 };
		int j{ axis + 2 };
		while (i >= 0 && j < rock.width) {
			if (rock.vertical[i] != rock.vertical[j]) {
				return false;
			}

			i--;
			j++;
		}
		return true;
	}
	else {
		int i{ axis - 1 };
		int j{ axis + 2 };
		while (i >= 0 && j < rock.height) {
			if (rock.horizontal[i] != rock.horizontal[j]) {
				return false;
			}

			i--;
			j++;
		}
		return true;
	}
}

bool Day13::checkSymDiff(Rock const& rock, bool dirVert, int axis) const {
	if (dirVert) {
		bool foundDiff{ false };
		int i{ axis };
		int j{ axis + 1 };
		while (i >= 0 && j < rock.width) {
			if (size_t diff = (rock.vertical[i] ^ rock.vertical[j]).count(); diff == 1) {
				foundDiff = true;
			}
			else if (diff > 1) {
				return false;
			}

			i--;
			j++;
		}
		return foundDiff;
	}
	else {
		bool foundDiff{ false };
		int i{ axis };
		int j{ axis + 1 };
		while (i >= 0 && j < rock.height) {
			if (size_t diff = (rock.horizontal[i] ^ rock.horizontal[j]).count(); diff == 1) {
				foundDiff = true;
			}
			else if (diff > 1) {
				return false;
			}

			i--;
			j++;
		}
		return foundDiff;
	}
}