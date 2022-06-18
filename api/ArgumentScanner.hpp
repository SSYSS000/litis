#pragma once

#include <string>
#include "ArgumentStack.hpp"
#include "Option.hpp"

class OptionScanner;

struct ScannedArguments
{
	std::vector<std::string> operands;
	std::vector<Option> options;
};

class ArgumentScanner
{
public:
	ArgumentScanner(OptionScanner* opt_scanner = nullptr);

	void set_option_scanner(OptionScanner* opt_scanner);
	ScannedArguments scan(ArgumentStack& stack);

private:
	OptionScanner* m_opt_scanner;
};
