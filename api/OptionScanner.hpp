#pragma once

#include <optional>
#include <string>
#include "Option.hpp"
#include "ArgumentStack.hpp"

class OptionScanner
{
public:
	OptionScanner(std::string short_opt_prefix,
		      std::string long_opt_prefix,
		      std::string end_of_opts);

	virtual ~OptionScanner() = default;

	virtual bool scan_next(ArgumentStack& stack, std::vector<Option>& out) = 0;

protected:
	bool is_option(const std::string& prefix, const std::string& str);
	bool is_long_option(const std::string& str);
	bool is_short_option(const std::string& str);

	bool m_opt_scanning = true;
	std::string m_short_opt_prefix;
	std::string m_long_opt_prefix;
	std::string m_end_of_opts;
};
