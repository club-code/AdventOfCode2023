#include "Day8.h"

#include <array>

day_t Day8::run() {
	auto input = readInputFromFile(getDayInputPath());
	parseInput(input);

	return part2();
}

day_t Day8::part1() {
	day_t iterations{ 0 };

	Node* currentNode{ startingNode };
	for (; currentNode != endingNode; iterations++) {
		std::cout << "Node " << currentNode->label;
		if (dir[iterations % dir.size()]) {
			currentNode = currentNode->right;
		}
		else {
			currentNode = currentNode->left;
		}
		std::cout << " goes to " << currentNode->label << '\n';
	}

	return iterations;
}

day_t Day8::part2() {
	day_t iterations{ 0 };

	std::vector<Node*> currentNodes{ startingNodes };
	currentNodes.shrink_to_fit();
	for (;; iterations++) {
		bool allEndings{ true };
		bool right{ dir[iterations % dir.size()] };
		for (auto& node : currentNodes) {
			//std::cout << node->label << " -> ";

			if (right) {
				node = node->right;
			}
			else {
				node = node->left;
			}

			//std::cout << node->label;

			allEndings &= node->label[2] == 'Z';

			//std::cout << " | ";
		}
		//std::cout << '\n';

		if (allEndings) {
			return iterations + 1;
		}
	}
}

void Day8::parseInput(std::vector<std::string> const& input) {
	for (auto c : input.front()) {
		if (c == 'L') {
			dir.emplace_back(false);
		}
		else {
			dir.emplace_back(true);
		}
	}
	dir.shrink_to_fit();

	// Reserve the memory for the nodes
	nodes.reserve(input.size() - 2);

	std::unique_ptr<std::array<Node*, 26 * 26 * 26>> tmpNodes{ std::make_unique<std::array<Node*, 26 * 26 * 26>>() };
	tmpNodes->fill(nullptr);

	// Find all the nodes
	for (auto it{ input.begin() + 2 }; it != input.end(); it++) {
		nodes.emplace_back(std::make_unique<Node>(it->substr(0, 3)));

		int id{ getIdx(it->substr(0, 3)) };
		(*tmpNodes)[id] = nodes.back().get();

		if ((*it)[2] == 'A') {
			startingNodes.emplace_back(nodes.back().get());
		}
	}

	// Link the nodes
	auto nodeIt{ nodes.begin() };
	for (auto it{ input.begin() + 2 }; it != input.end(); (it++, nodeIt++)) {
		int idL{ getIdx(it->substr(7, 3)) };
		int idR{ getIdx(it->substr(12, 3)) };

		if ((*tmpNodes)[idL] == nullptr)
			std::cout << "Error: " << *it << " has no left node" << std::endl;
		if ((*tmpNodes)[idR] == nullptr)
			std::cout << "Error: " << *it << " has no right node" << std::endl;

		(*nodeIt)->left = (*tmpNodes)[idL];
		(*nodeIt)->right = (*tmpNodes)[idR];

		std::cout << "Node " << (*nodeIt)->label << " has left node " << (*nodeIt)->left->label << " and right node " << (*nodeIt)->right->label << "\n";
	}

	// Find the starting node
	startingNode = tmpNodes->front();
	endingNode = tmpNodes->back();
}
