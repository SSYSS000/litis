#include <cassert>
#include <cctype>
#include <algorithm>
#include "OptionScanner.hpp"

bool starts_with(const std::string& prefix, const std::string& operand)
{
	return operand.length() >= prefix.length() &&
		std::equal(prefix.begin(), prefix.end(), operand.begin());
}

OptionScanner::OptionScanner(std::string short_opt_prefix, std::string long_opt_prefix, std::string end_of_opts) :
	m_short_opt_prefix(std::move(short_opt_prefix)),
	m_long_opt_prefix(std::move(long_opt_prefix)),
	m_end_of_opts(std::move(end_of_opts))
{
	assert(m_short_opt_prefix.length() < m_long_opt_prefix.length());
}

bool OptionScanner::is_option(const std::string& prefix, const std::string& str)
{
	return str.length() > prefix.length() &&
			starts_with(prefix, str) &&
			std::isalpha(str[prefix.length()]);
}

bool OptionScanner::is_long_option(const std::string& str)
{
	return is_option(m_long_opt_prefix, str);
}

bool OptionScanner::is_short_option(const std::string& str)
{
	return is_option(m_short_opt_prefix, str);
}
