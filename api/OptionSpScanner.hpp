#pragma once

#include <vector>
#include <set>
#include <string>
#include "OptionScanner.hpp"
#include "ArgumentStack.hpp"

class Option;

class OptionSpScanner: public OptionScanner
{
public:
	OptionSpScanner(std::string short_opt_prefix = "-",
			  std::string long_opt_prefix = "--",
			  std::string end_of_opts = "--");

	void expect_value(std::string option_no_pfx);

	bool scan_next(ArgumentStack& stack, std::vector<Option>& out) override;

private:
	bool is_value_expected(char option_no_pfx) const;
	bool is_value_expected(const std::string& option_no_pfx) const;
	std::set<std::string> m_value_opts;
};
