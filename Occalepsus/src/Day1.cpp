#include "Day1.h"

#include <map>

const std::map<int, std::string> numbers = {
	{0, "zero"},
	{1, "one"},
	{2, "two"},
	{3, "three"},
	{4, "four"},
	{5, "five"},
	{6, "six"},
	{7, "seven"},
	{8, "eight"},
	{9, "nine"}
};

int Day1::run() {
	auto input = readInputFromFile(getDayInputPath());

	return part2(input);
}

int Day1::part1(std::vector<std::string> const& input) const {
	int res = 0;
	for (auto const& line : input) {
		int a = findLine(line);
		res += a;
		std::cout << "Read line: " << line << " -> " << a << "\n";
	}
	return res;
}

int Day1::findLine(std::string_view const& line) const {
	int res = 0;
	for (auto it = line.begin(); it != line.end(); ++it) {
		if (*it >= '0' && *it <= '9') {
			res += 10 * (*it - '0');
			break;
		}
	}
	for (auto it = line.rbegin(); it != line.rend(); ++it) {
		if (*it >= '0' && *it <= '9') {
			res += *it - '0';
			break;
		}
	}
	return res;
}

int Day1::part2(std::vector<std::string> const& input) const {
	int res = 0;
	for (auto const& line : input) {
		int a = findLine2(line);
		res += a;
		std::cout << "Read line: " << line << " -> " << a << "\n";
	}
	return res;
}

int Day1::findLine2(std::string_view const& line) const {
	size_t first = line.size();
	int fvalue = -1;

	size_t last = 0;
	int lvalue = -1;

	for (auto it = line.begin(); it != line.end(); ++it) {
		if (*it >= '0' && *it <= '9') {
			first = it - line.begin();
			fvalue = *it - '0';
			break;
		}
	}
	for (auto it = line.rbegin(); it != line.rend(); ++it) {
		if (*it >= '0' && *it <= '9') {
			last = line.size() - (it - line.rbegin()) - 1;
			lvalue = *it - '0';
			break;
		}
	}

	for (auto const& [v, w] : numbers) {
		size_t p;
		if ((p = line.find(w)) != std::string::npos && p < first) {
			first = p;
			fvalue = v;
		}

		if ((p = line.rfind(w)) != std::string::npos && p >= last) {
			last = p;
			lvalue = v;
		}
	}

	return 10 * fvalue + lvalue;
}