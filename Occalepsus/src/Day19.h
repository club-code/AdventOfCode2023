#pragma once

#include "util/DayInterface.h"

#include <array>

using day_t = long;

class Day19 : public DayInterface<day_t>
{
public:
	Day19() : DayInterface(R"(C:\Users\jujuj\Documents\Projets informatique\AdventOfCode2023\input\InputDay19.txt)") {};
	~Day19() override = default;

	day_t run() override;

private:
	using Part = std::array<day_t, 4>;

	enum PartCaract {
		X,
		M,
		A,
		S
	};

	enum Status {
		Accepted,
		Rejected,
		Goto
	};

	struct Workflow;
	struct Action {
		Status status{ Status::Accepted };
		std::string_view nextLabel{};
		Workflow* nextWorkflow{ nullptr };

		Action() = default;
		explicit Action(std::string_view const& str);
		void link(std::vector<Workflow>& workflowsToLink);
	};

	struct SubProcess {
		PartCaract partName;
		bool inferior;
		day_t compare;
		Action action;

		SubProcess(PartCaract partName, bool inferior, day_t compare, Action const& action):
			partName(partName), inferior(inferior), compare(compare), action(action) {};
		bool run(Part const& part) const;
	};

	struct Workflow {
		std::string_view label;
		std::vector<SubProcess> subProcesses;
		Action defaultAction;

		explicit Workflow(std::string_view const& input);
		Action process(Part const& part) const;
	};

	std::vector<Workflow> workflows;
	Workflow* startWorkflow{ nullptr };

	std::vector<Part> parts;

	day_t part1() const;
	day_t part2();
	void parseInput(std::vector<std::string> const& input);
	static PartCaract getPartCaract(char c);
	static Part parsePart(std::string_view const& str);
};
