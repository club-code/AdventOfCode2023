#include "Day15.h"

#include <algorithm>

day_t Day15::run() {
	auto input = readInputFromFile(getDayInputPath());
	parseInput(input);

	return part2();
}

day_t Day15::part1() {
	day_t res{ 0 };

	for (auto& queue : inputQueues) {
		day_t hash{ 0 };
		char c;
		while (!queue.empty()) {
			c = queue.front();
			std::cout << c;
			queue.pop();
			hashAppendChar(c, hash);
		}
		std::cout << " => " << hash << "\n";
		res += hash;
	}

	return res;
}

day_t Day15::part2() {
	day_t res{ 0 };

	for (auto const& step : steps) {
		int hash{ hashString(step.label) };

		// Case '-'
		if (step.length == 0) {
			// If found in map[hash]
			if (auto it{ 
				std::find_if(map[hash].begin(), map[hash].end(),
					[&step](Step const& s) { return s.label == step.label; })
				};
				it != map[hash].end()) {

				map[hash].erase(it);
			}
		}
		else {
			// If found in map[hash]
			if (auto it{
				std::find_if(map[hash].begin(), map[hash].end(),
					[&step](Step const& s) { return s.label == step.label; })
				};
				it != map[hash].end()) {

				it->length = step.length;
			}
			else {
				map[hash].push_back(step);
			}
		}
	}

	for (auto boxIt{ map.begin() }; boxIt != map.end(); boxIt++) {
		// Count the lenses we have iterated through, since list::iterator is not random access
		int lensCount{ 0 };
		for (auto lensIt{ boxIt->begin() }; lensIt != boxIt->end(); lensIt++) {
			lensCount++;
			res += (boxIt - map.begin() + 1) * lensCount * lensIt->length;
		}
	}

	return res;
}

void Day15::parseInput(std::vector<std::string> const& input) {
	std::queue<char> queue;
	Step step;

	// For each character in the input in each line
	for (auto const& line : input) /* and */ for (auto const& c : line) {
		if (c == ',') {
			inputQueues.push_back(queue);
			queue = std::queue<char>();

			steps.push_back(step);
			step = Step();
		}
		else {
			queue.push(c);

			if (c == '-') {
				step.length = 0;
			}
			else if (c == '=') {
				continue;
			}
			else if (c >= '1' && c <= '9') {
				step.length = c - '0';
			}
			else {
				step.label += c;
			}
		}
	}
	inputQueues.push_back(queue);
	steps.push_back(step);
}

void Day15::hashAppendChar(char c, day_t& hash) const {
	hash = ((hash + c) * 17) % 256;
}

int Day15::hashString(std::string_view const& str) const {
	int hash{ 0 };

	for (auto c : str) {
		hashAppendChar(c, hash);
	}

	return hash;
}
