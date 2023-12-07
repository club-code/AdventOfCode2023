#include "Day4.h"

int Day4::run() {
	auto input = readInputFromFile(getDayInputPath());

	return part2(input);
}

int Day4::part1(std::vector<std::string> const& input) {
	parseInput(input);

	int res = 0;

	int id{ 0 };
	for (auto& card : cards) {
		std::cout << "Card " << id << ": ";
		for (auto w : card.winning) {
			for (auto s : card.scratched) {
				if (w == s) {
					if (card.score == 0) {
						card.score = 1;
					}
					else {
						card.score <<= 1;
					}
					std::cout << w << " ";
				}
			}
		}
		std::cout << "| score: " << card.score << "\n";
		res += card.score;
	}

	return res;
}

int Day4::part2(std::vector<std::string> const& input) {
	parseInput(input);

	int res = 0;

	for (auto card{ cards.begin() }; card < cards.end(); card++) {
		for (auto w : card->winning) {
			for (auto s : card->scratched) {
				if (w == s) {
					card->score++;
				}
			}
		}

		res += card->copies;

		auto otherCard{ card + 1 };
		int copies{ card->score };
		while (copies > 0) {
			otherCard->copies += card->copies;
			copies--;
			otherCard++;
		}
	}

	return res;
}

void Day4::parseInput(std::vector<std::string> const& input) {
	for (auto const& line : input) {
		cards.emplace_back();
		int state{ 0 };
		int tempValue{ 0 };

		for (auto c : line) {
			if (state == 0 && c == ':') {
				state = 1;
			}
			else if (state == 1 && c == '|') {
				state = 2;
			}
			else if (c == ' ' && tempValue != 0) {
				if (state == 1) {
					cards.back().winning.push_back(tempValue);
				}
				else if (state == 2) {
					cards.back().scratched.push_back(tempValue);
				}
				tempValue = 0;
			}
			else if (c >= '0' && c <= '9' && state > 0) {
				tempValue *= 10;
				tempValue += c - '0';
			}
		}
		cards.back().scratched.push_back(tempValue);
	}
}