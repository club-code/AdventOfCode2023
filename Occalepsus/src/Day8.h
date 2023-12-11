#pragma once

#include "util/DayInterface.h"

using day_t = size_t;

class Day8 : public DayInterface<day_t>
{
public:
	Day8() : DayInterface(R"(C:\Users\jujuj\Documents\Projets informatique\AdventOfCode2023\input\InputDay8.txt)") {};
	~Day8() override = default;

	day_t run() override;

private:
	/// false = left, true = right
	std::vector<bool> dir;

	struct Node {
		std::string label;
		Node* left{ nullptr };
		Node* right{ nullptr };

		explicit Node(std::string const& label) : label(label) {};
	};

	std::vector<std::unique_ptr<Node>> nodes;

	Node* startingNode{ nullptr };
	std::vector<Node*> startingNodes;

	Node* endingNode{ nullptr };

	day_t part1();
	day_t part2();
	void parseInput(std::vector<std::string> const& input);
	int getIdx(std::string const& label) const {
		if (label.size() != 3) {
			throw std::runtime_error("Label size is not 3");
		}
		return (label[0] - 'A') * 26 * 26 + (label[1] - 'A') * 26 + (label[2] - 'A');
	}
};
