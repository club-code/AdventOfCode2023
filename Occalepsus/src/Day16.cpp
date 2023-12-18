#include "Day16.h"

day_t Day16::run() {
	auto input = readInputFromFile(getDayInputPath());
	parseInput(input);

	return part2();
}

day_t Day16::part1() {
	day_t res{ 0 };

	raysToCompute.push(Ray(0, 0, Direction::East));

	while (!raysToCompute.empty()) {
		if (!stepRay(raysToCompute.front(), globalMap)) {
			raysToCompute.pop();
		}
	}

	for (auto const& line : globalMap) {
		for (auto const& tile : line) {
			if (tile.energetized) {
				res++;
				std::cout << '#';
			}
			else {
				std::cout << '.';
			}
		}
		std::cout << '\n';
	}
	std::cout << '\n';

	return res;
}

day_t Day16::part2() {
	day_t res{ 0 };

	for (int i{ 0 }; i < map_size; i++) {
		for (int dir{ 0 }; dir < 4; dir++) {
			auto mapCpy{ globalMap };

			switch (dir) {
			case 0:
				raysToCompute.push(Ray(i, map_size - 1, Direction::North));
				break;
			case 1:
				raysToCompute.push(Ray(0, i, Direction::East));
				break;
			case 2:
				raysToCompute.push(Ray(i, 0, Direction::South));
				break;
			case 3:
				raysToCompute.push(Ray(map_size - 1, i, Direction::West));
				break;
			default:
				break;
			}

			while (!raysToCompute.empty()) {
				if (!stepRay(raysToCompute.front(), mapCpy)) {
					raysToCompute.pop();
				}
			}

			day_t val{ 0 };
			for (auto const& line : mapCpy) {
				for (auto const& tile : line) {
					if (tile.energetized) {
						val++;
					}
				}
			}
			if (val > res) {
				res = val;
			}
		}
	}

	return res;
}

void Day16::parseInput(std::vector<std::string> const& input) {
	int x{ 0 };
	int y{ 0 };
	for (auto const& line : input) {
		for (auto c : line) {
			switch (c) {
			case '\\':
				globalMap[y][x] = Tile(TileType::MirrorA);
				break;
			case '/':
				globalMap[y][x] = Tile(TileType::MirrorB);
				break;
			case '-':
				globalMap[y][x] = Tile(TileType::SplitterEW);
				break;
			case '|':
				globalMap[y][x] = Tile(TileType::SplitterNS);
				break;
			default:
				globalMap[y][x] = Tile(TileType::Empty);
				break;
			}
			x++;
		}
		x = 0;
		y++;
	}
}

// Returns false if the ray has been destroyed, newRay is a new ray to compute
bool Day16::stepRay(Ray& ray, map_t& map) {
	// Alias for the tile the ray is currently on
	auto& tile = map[ray.y][ray.x];

	// If the ray is already energized in that direction, it's a loop, destroy it
	if (tile.lightDirNESW[ray.dir]) {
		return false;
	}

	// Mark the tile as energized
	tile.lightDirNESW[ray.dir] = true;
	tile.energetized = true;

	// Reflect the ray, and destroy and create new rays if needed
	switch (tile.type) {
	case TileType::Empty:
		break;
	case TileType::MirrorA:
		switch (ray.dir) {
		case Direction::North:
			ray.dir = Direction::West;
			break;
		case Direction::East:
			ray.dir = Direction::South;
			break;
		case Direction::South:
			ray.dir = Direction::East;
			break;
		case Direction::West:
			ray.dir = Direction::North;
			break;
		}
		break;
	case TileType::MirrorB:
		switch (ray.dir) {
		case Direction::North:
			ray.dir = Direction::East;
			break;
		case Direction::East:
			ray.dir = Direction::North;
			break;
		case Direction::South:
			ray.dir = Direction::West;
			break;
		case Direction::West:
			ray.dir = Direction::South;
			break;
		}
		break;
	case TileType::SplitterEW:
		switch (ray.dir) {
		case Direction::North:
		case Direction::South:
			raysToCompute.push(Ray(ray.x, ray.y, Direction::East));
			raysToCompute.push(Ray(ray.x, ray.y, Direction::West));
			// This ray is destroyed
			return false;
		default:
			break;
		}
		break;
	case TileType::SplitterNS:
		switch (ray.dir) {
		case Direction::East:
		case Direction::West:
			raysToCompute.push(Ray(ray.x, ray.y, Direction::North));
			raysToCompute.push(Ray(ray.x, ray.y, Direction::South));
			return false;
		default:
			break;
		}
		break;
	}

	// Advance the ray
	ray.advance();

	// If the ray is out of bounds, destroy it
	return ray.x >= 0 && ray.x < map_size && ray.y >= 0 && ray.y < map_size;
}

void Day16::Ray::advance() {
	switch (dir) {
	case Direction::North:
		y--;
		break;
	case Direction::East:
		x++;
		break;
	case Direction::South:
		y++;
		break;
	case Direction::West:
		x--;
		break;
	}
}
