#pragma once

#include "util/DayInterface.h"

#include <array>
#include <queue>

constexpr int map_size = 110;

using day_t = int;

class Day16 : public DayInterface<day_t>
{
public:
	Day16() : DayInterface(R"(C:\Users\jujuj\Documents\Projets informatique\AdventOfCode2023\input\InputDay16.txt)") {};
	~Day16() override = default;

	day_t run() override;

private:
	enum Direction {
		North,
		East,
		South,
		West,
	};

	struct Ray {
		int x;
		int y;
		Direction dir;

		Ray() = default;
		Ray(int x, int y, Direction dir): x(x), y(y), dir(dir) {};

		void advance();
	};

	std::queue<Ray> raysToCompute;

	enum TileType {
		SplitterNS,
		SplitterEW,
		// Mirror from top left to bottom right
		MirrorA,
		// Mirror from top right to bottom left
		MirrorB,
		Empty,
	};

	struct Tile {
		TileType type{ Empty };
		std::array<bool, 4> lightDirNESW{};
		bool energetized{ false };

		Tile() = default;
		explicit Tile(TileType type): type(type) {};
	};

	using map_t = std::array<std::array<Tile, map_size>, map_size>;
	map_t globalMap;

	day_t part1();
	day_t part2();
	void parseInput(std::vector<std::string> const& input);
	bool stepRay(Ray& ray, map_t& map);
};
