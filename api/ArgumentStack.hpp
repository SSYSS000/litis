#pragma once

#include <stack>
#include <string>
#include <vector>

using ArgumentStack = std::stack<std::string, std::vector<std::string>>;

ArgumentStack make_arg_stack(int argc, const char* const* argv);
