#pragma once

#include <vector>
#include <string>
#include "OptionMap.hpp"

template<typename AccessorT>
struct Arguments
{
	std::string executable;
	OptionMap<AccessorT> options;
	std::vector<std::string> operands;
};
