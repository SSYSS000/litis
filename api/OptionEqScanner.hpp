#pragma once

#include <vector>
#include <string>
#include <string_view>
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
	bool is_option(const std::string& prefix, std::string_view str);
	bool is_long_option(std::string_view str);
	bool is_short_option(std::string_view str);
	char m_opt_value_delimiter = '=';

};
