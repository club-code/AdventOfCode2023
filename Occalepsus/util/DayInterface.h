#pragma once

#include "inputReader.h"

#include <string>
#include <vector>
#include <iostream>

template<typename T>
class DayInterface
{
public:
	virtual ~DayInterface() = 0;

	std::string getDayInputPath() const { return dayInputPath; }

	virtual T run() = 0;

protected:
	explicit DayInterface(std::string const& dayInputPath) : dayInputPath(dayInputPath) {}

private:
	const std::string dayInputPath;
	
	DayInterface() = default;
};

template<typename T>
DayInterface<T>::~DayInterface() = default;