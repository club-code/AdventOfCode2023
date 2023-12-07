#include "Day6.h"

day_t Day6::run() {
	auto input = readInputFromFile(getDayInputPath());
	parseInput(input);

	return part2();
}

day_t Day6::part1() const {
	int res{ 1 };

	for (auto const& record : records) {
		std::cout << record.time << " " << record.distance;

		// We take the discriminant of the distance function d(t) = -t^2 + T*t - db (with T = record.time and db = record.distance)
		auto sqrtDelta{ sqrt(record.time * record.time - 4 * record.distance) };

		// Count the number of possible values (did not find a better way to do it)
		int range{ 0 };
		for (int i{ static_cast<int>(floor((record.time - sqrtDelta) / 2)) + 1 }; i <= static_cast<int>(ceil((record.time + sqrtDelta) / 2)) - 1; i++) {
			range++;
		}

		std::cout << " found " << range << " possible values\n";

		res *= range;

	}

	return res;
}

day_t Day6::part2() const {
	std::cout << singleRecord.time << " " << singleRecord.distance;

	// We take the discriminant of the distance function d(t) = -t^2 + T*t - db (with T = record.time and db = record.distance)
	auto sqrtDelta{ sqrt(singleRecord.time * singleRecord.time - 4LL * singleRecord.distance) };
	
	// Count the number of possible values (did not find a better way to do it)
	day_t range{ 0 };
	for (day_t i{ static_cast<day_t>(floor((singleRecord.time - sqrtDelta) / 2)) + 1 }; i <= static_cast<day_t>(ceil((static_cast<double>(singleRecord.time) + sqrtDelta) / 2)) - 1; i++) {
		range++;
	}

	std::cout << " found " << range << " possible values\n";

	return range;
}

void Day6::parseInput(std::vector<std::string> const& input) {
	Record tempRecord{ 0, 0 };
	for (auto it{ input.front().begin() + input.front().find(':') + 1 }; it < input.front().end(); it++) {
		if (*it == ' ' && tempRecord.time > 0) {
			records.push_back(tempRecord);
			tempRecord.time = 0;
			tempRecord.distance = 0;
		}
		else if (*it >= '0' && *it <= '9') {
			tempRecord.time *= 10;
			tempRecord.time += *it - '0';

			// For part2
			singleRecord.time *= 10;
			singleRecord.time += *it - '0';
		}
	}
	records.push_back(tempRecord);

	auto recordsIt{ records.begin() };
	for (auto it{ input.back().begin() + input.front().find(':') + 1 }; it < input.back().end(); it++) {
		if (*it == ' ' && recordsIt->distance > 0) {
			recordsIt++;
		}
		else if (*it >= '0' && *it <= '9') {
			recordsIt->distance *= 10;
			recordsIt->distance += *it - '0';

			// For part2
			singleRecord.distance *= 10;
			singleRecord.distance += *it - '0';
		}
	}
}
