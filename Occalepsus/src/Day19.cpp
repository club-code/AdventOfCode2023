#include "Day19.h"

#include <algorithm>
#include <numeric>

day_t Day19::run() {
	auto input = readInputFromFile(getDayInputPath());
	parseInput(input);

	std::cout << "Input parsed\n";

	return part1();
}

day_t Day19::part1() const {
	day_t res{ 0 };

	for (auto const& part : parts) {
		std::cout << "Part: x=" << part[PartCaract::X] << " m=" << part[PartCaract::M] << " a=" << part[PartCaract::A] << " s=" << part[PartCaract::S];
		Workflow const* currentWorkflow{ startWorkflow };
		for (;;) {
			std::cout << " -> " << currentWorkflow->label;
			if (Action const& action{ currentWorkflow->process(part) }; action.status == Status::Goto) {
				currentWorkflow = action.nextWorkflow;
				continue;
			}
			else if (action.status == Status::Accepted) {
				res += std::accumulate(part.begin(), part.end(), 0);
				std::cout << " => Accepted with " << res << "\n";
			}
			else {
				std::cout << " => Rejected\n";
			}
			break;
		}
	}

	return res;
}

day_t Day19::part2() {
	day_t res{ 0 };

	return res;
}

void Day19::parseInput(std::vector<std::string> const& input) {
	for (auto const& line : input) {
		if (!line.empty()) {
			if (line[0] == '{') {
				parts.emplace_back(parsePart(line));
			}
			else {
				workflows.emplace_back(line);
			}
		}
	}

	for (auto& workflow : workflows) {
		for (auto& subProcess : workflow.subProcesses) {
			subProcess.action.link(workflows);
		}
		workflow.defaultAction.link(workflows);

		if (workflow.label == "in") {
			startWorkflow = &workflow;
		}
	}
}

Day19::PartCaract Day19::getPartCaract(char c) {
	switch (c) {
	case 'x':
		return PartCaract::X;
	case 'm':
		return PartCaract::M;
	case 'a':
		return PartCaract::A;
	case 's':
		return PartCaract::S;
	default:
		exit(1);
	}
}

Day19::Part Day19::parsePart(std::string_view const& str) {
	Part res{};
	size_t pos{ str.find("x=") + 2 };
	size_t endPos{ str.find(',', pos) };
	res[PartCaract::X] = std::stoi(std::string(str.substr(pos, endPos - pos)));

	pos = str.find("m=") + 2;
	endPos = str.find(',', pos);
	res[PartCaract::M] = std::stoi(std::string(str.substr(pos, endPos - pos)));

	pos = str.find("a=") + 2;
	endPos = str.find(',', pos);
	res[PartCaract::A] = std::stoi(std::string(str.substr(pos, endPos - pos)));

	pos = str.find("s=") + 2;
	endPos = str.find('}', pos);
	res[PartCaract::S] = std::stoi(std::string(str.substr(pos, endPos - pos)));

	return res;
}

Day19::Workflow::Workflow(std::string_view const& input) {
	size_t pos{ input.find('{') };
	label = input.substr(0, pos);

	for (;;) {
		if (size_t semiPos; (semiPos = input.find(':', pos)) == std::string::npos) {
			defaultAction = Action(input.substr(pos + 1, input.size() - pos - 2));
			break;
		}
		else {
			day_t compare{ 0 };
			for (size_t tpos{ pos + 3 }; tpos < semiPos; tpos++) {
				compare *= 10;
				compare += input[tpos] - '0';
			}

			size_t commaPos{ input.find(',', semiPos) };

			subProcesses.emplace_back(getPartCaract(input[pos + 1]), input[pos + 2] == '<', compare, Action(input.substr(semiPos + 1, commaPos - semiPos - 1)));
			
			pos = commaPos;
		}
	}
}

Day19::Action Day19::Workflow::process(Part const& part) const {
	for (auto const& subProcess : subProcesses) {
		if (subProcess.run(part)) {
			return subProcess.action;
		}
	}
	return defaultAction;
}

bool Day19::SubProcess::run(Part const& part) const {
	if (inferior) {
		return part[partName] < compare;
	}
	else {
		return part[partName] > compare;
	}
}

Day19::Action::Action(std::string_view const& strAction) {
	if (strAction == "A") {
		status = Status::Accepted;
	}
	else if (strAction == "R") {
		status = Status::Rejected;
	}
	else {
		status = Status::Goto;
		nextLabel = strAction;
	}
}

void Day19::Action::link(std::vector<Workflow>& workflowsToLink) {
	if (status != Status::Goto) {
		return;
	}

	if (std::vector<Workflow>::iterator it; (it = std::find_if(workflowsToLink.begin(), workflowsToLink.end(),
		[this](Workflow const& other) {
			return nextLabel == other.label;
		}
	)) != workflowsToLink.end()) {
		nextWorkflow = &(*it);
	}
	else {
		std::cout << "Error: Workflow " << nextLabel << " not found\n";
	}
}
