#include "Day5.h"

#include <limits>

long long Day5::run() {
	auto input = readInputFromFile(getDayInputPath());

	parseInput(input, false);

	return part2();
}

long long Day5::part1() const {
	// Since we want the minimum value, we start from the maximum value
	long long res{ std::numeric_limits<long long>::max() };

	for (auto const& seed : seeds) {
		long long value{ seed.start };
		std::cout << "Seed: " << value;
		for (auto const& map : almanac) {
			for (auto const& range : map.ranges) {
				// Checks if value is in the range
				if (value >= range.src && value < range.src + range.size) {
					value += range.dest - range.src;
					break;
				}
			}
			std::cout << " -> " << value;
		}

		if (value < res) {
			std::cout << " (new min)";
			res = value;
		}

		std::cout << "\n";
	}

	return res;
}

long long Day5::part2() const {
	// Since we want the minimum value, we start from the maximum value
	long long res{ std::numeric_limits<long long>::max() };

	for (auto const& seed : seeds) {
		std::vector<SeedRange> seedRanges{ seed };
		for (auto const& map : almanac) {
			std::vector<SeedRange> seedRangesToAdd;
			for (auto& seedRange : seedRanges) {
				auto newRanges{ checkSeedRange(seedRange, map) };
				seedRangesToAdd.insert(seedRangesToAdd.begin(), newRanges.begin(), newRanges.end());
			}
			seedRanges.insert(seedRanges.end(), seedRangesToAdd.begin(), seedRangesToAdd.end());
		}

		for (auto const& seedRange : seedRanges) {
			std::cout << "Seed range from " << seedRange.start << " to " << seedRange.end;
			if (seedRange.start < res) {
				std::cout << " (new min)";
				res = seedRange.start;
			}
			std::cout << "\n";
		}
	}

	return res;
}


std::vector<Day5::SeedRange> Day5::checkSeedRange(SeedRange& seed, RangeMap const& ranges) const {
	std::vector<Day5::SeedRange> res;

	for (auto const& range : ranges.ranges) {
		// Case 1: Everything before		|--| x-----x
		if (seed.end < range.src) {
			// Nothing to do
			continue;
		}

		// Case 2: Everything after				 x-----x |--|
		else if (seed.start >= range.src + range.size) {
			// Nothing to do
			continue;
		}

		// Case 3: Overlap start			|----x--|--x
		else if (seed.start < range.src && seed.end < range.src + range.size) {
			// We create a new seed range, which has been well placed
			res.emplace_back(range.dest, seed.end - range.src + range.dest);
			seed.end = range.src;
			continue;
		}

		// Case 4: Contained and bigger		|----x-----x----|
		else if (seed.start < range.src && seed.end >= range.src + range.size) {
			// We create a new seed range, which has been well placed
			res.emplace_back(range.dest, range.size + range.dest);

			// Compute the end of the seed range (not really good, but I don't know how to do better)
			SeedRange endSeed{ range.src + range.size, seed.end };
			auto endRes{ checkSeedRange(endSeed, ranges) };
			res.insert(res.end(), endRes.begin(), endRes.end());
			res.emplace_back(endSeed);

			seed.end = range.src;
			continue;
		}

		// Case 5: Contained and smaller		 x-|-|-x
		else if (seed.start >= range.src && seed.end < range.src + range.size) {
			// We change the seed range, which is now well placed, so we return
			seed.start += range.dest - range.src;
			seed.end += range.dest - range.src;
			return res;
		}

		// Case 6: Overlap end					 x--|--x----|
		else if (seed.start >= range.src && seed.end >= range.src + range.size) {
			// We create a new seed range, which has been well placed
			res.emplace_back(seed.start - range.src + range.dest, range.dest + range.size);
			seed.start = range.src + range.size;
			continue;
		}
	}
	return res;
}


void Day5::parseInput(std::vector<std::string> const& input, bool part1) {
	int id{ -1 };

	for (auto const& line : input) {
		// Case empty line
		if (line.size() == 0) {
			id++;
			continue;
		}
		// Case first line with seed list
		else if (id < 0) {
			size_t pos{ 7 };
			while (pos < line.size()) {
				size_t end{ line.find(" ", pos) };
				if (end == std::string::npos) {
					end = line.size();
				}
				
				// Case of the start of the range (one out of two) or if we are in part 1
				if (part1 || id == -1) {
					seeds.emplace_back(std::stoll(line.substr(pos, end - pos)), -1);
					id = part1 ? -1 : -2;
				}
				// Case of the size of the range, transform into the end of the range (the other one)
				else {
					seeds.back().end = seeds.back().start + std::stoll(line.substr(pos, end - pos));
					id = -1;
				}
				pos = end + 1;
			}
		}
		// Case line with ranges (not the first lines with the texts)
		else if (line[0] >= '0' && line[0] <= '9') {
			size_t first{ line.find(" ") };
			size_t second{ line.find(" ", first + 1) };

			almanac[id].ranges.emplace_back(
				// Source
				std::stoll(line.substr(first + 1, second - first)),
				// Destination
				std::stoll(line.substr(0, first)),
				// Size
				std::stoll(line.substr(second, second - line.size()))
			);
		}
	}
}