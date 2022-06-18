#pragma once

#include <vector>
#include <string>
#include "Option.hpp"
#include "OptionScanner.hpp"

class OptionEqScanner : public OptionScanner
{
public:
	OptionEqScanner(std::string short_opt_prefix = "-",
		      std::string long_opt_prefix = "--",
		      std::string end_of_opts = "--");

	bool scan_next(ArgumentStack& stack, std::vector<Option>& out) override;

private:
	char m_opt_value_delimiter = '=';

};
