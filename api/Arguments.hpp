#pragma once

#include <string>
#include <vector>

#include "OptionMap.hpp"

template <typename AccessorT>
struct Arguments
{
    std::string executable;
    OptionMap<AccessorT> options;
    std::vector<std::string> operands;
};
