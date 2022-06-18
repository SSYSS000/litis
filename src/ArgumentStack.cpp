#include <iterator>
#include "ArgumentStack.hpp"

ArgumentStack make_arg_stack(int argc, const char* const* argv)
{
	return ArgumentStack(std::vector<std::string>(
			std::make_reverse_iterator(argv + argc),
			std::make_reverse_iterator(argv)));
}
