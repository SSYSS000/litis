#pragma once

#include <vector>
#include <stack>
#include <string_view>

using ArgumentStack = std::stack<std::string_view, std::vector<std::string_view>>;

ArgumentStack make_arg_stack(int argc, const char* const* argv);
