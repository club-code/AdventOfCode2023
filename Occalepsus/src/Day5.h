#pragma once

#include "util/DayInterface.h"

#include <array>

class Day5 : public DayInterface<long long>
{
public:
	Day5() : DayInterface(R"(C:\Users\jujuj\Documents\Projets informatique\AdventOfCode2023\input\InputDay5.txt)") {};
	~Day5() override = default;

	long long run() override;

private:
	struct SeedRange {
		long long start;
		long long end;
		SeedRange(long long start, long long end) : start(start), end(end) {};
		SeedRange(SeedRange const& other) = default;
		~SeedRange() = default;
	};

	std::vector<SeedRange> seeds;

	struct Range {
		long long src;
		long long dest;
		long long size;
		Range(long long src, long long dest, long long size) : src(src), dest(dest), size(size) {};
	};

	struct RangeMap {
		int id;
		std::vector<Range> ranges;
	};

	std::array<RangeMap, 7> almanac = {
		RangeMap{0},
		RangeMap{1},
		RangeMap{2},
		RangeMap{3},
		RangeMap{4},
		RangeMap{5},
		RangeMap{6}
	};

	long long part1() const;
	long long part2() const;
	std::vector<Day5::SeedRange> checkSeedRange(SeedRange& seedRange, RangeMap const& ranges) const;
	void parseInput(std::vector<std::string> const& input, bool part1 = true);
};
