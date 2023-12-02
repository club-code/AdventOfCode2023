#include "Day2.h"

int Day2::run() {
	auto input = readInputFromFile(getDayInputPath());

	return part2(input);
}

int Day2::part1(std::vector<std::string> const& input) const {
	int res = 0;

	int gIdx{ 0 };
	for (auto const& line : input) {
		res += ++gIdx;
		for (auto const& c : parseLine(line)) {
			//std::cout << c.r << " " << c.g << " " << c.b << std::endl;

			if (c.r > targetColor.r || c.g > targetColor.g || c.b > targetColor.b) {
				res -= gIdx;
				std::cout << "Game " << gIdx << " is impossible : " << c.r << " " << c.g << " " << c.b << std::endl;
				break;
			}
		}
	}

	return res;

}

int Day2::part2(std::vector<std::string> const& input) const {
	int res = 0;

	for (auto const& line : input) {
		ColorSet minColorSet{ 0, 0, 0 };

		for (auto const& c : parseLine(line)) {
			if (c.r > minColorSet.r) {
				minColorSet.r = c.r;
			}
			if (c.g > minColorSet.g) {
				minColorSet.g = c.g;
			}
			if (c.b > minColorSet.b) {
				minColorSet.b = c.b;
			}
		}

		std::cout << "Power of game: " << minColorSet.r * minColorSet.g * minColorSet.b << std::endl;
		res += minColorSet.r * minColorSet.g * minColorSet.b;
	}

	return res;
}

std::vector<Day2::ColorSet> Day2::parseLine(std::string const& line) const
{
	std::vector<Day2::ColorSet> res;
	Day2::ColorSet tempColorSet;

	// Game 11: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
	const std::regex lineRegex{ "^Game (?:[0-9]*): ((?:(?:(?:[0-9]* (?:red|green|blue))(?:, ?)*)(?:; )?)*)$" };
	const std::regex partRegex{ "([0-9]+) (red|green|blue)(, |; )?" };

	std::smatch matchLine;
	std::regex_match(line, matchLine, lineRegex);

	std::string partMatch{ matchLine[1].str() };
	while (std::regex_search(partMatch, matchLine, partRegex)) {
		if (matchLine[2].str() == "red") {
			tempColorSet.r = std::stoi(matchLine[1].str());
		}
		else if (matchLine[2].str() == "green") {
			tempColorSet.g = std::stoi(matchLine[1].str());
		}
		else if (matchLine[2].str() == "blue") {
			tempColorSet.b = std::stoi(matchLine[1].str());
		}

		if (matchLine[3].str() == "; " || matchLine[3].length() == 0) {
			res.push_back(tempColorSet);
			tempColorSet = Day2::ColorSet();
		}

		partMatch = matchLine.suffix().str();
	}

	return res;
}
