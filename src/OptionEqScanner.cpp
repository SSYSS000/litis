#include <string_view>
#include <string>
#include <algorithm>
#include <cctype>
#include "OptionEqScanner.hpp"

bool starts_with(std::string_view prefix, std::string_view operand)
{
	return operand.length() >= prefix.length() &&
		std::equal(prefix.begin(), prefix.end(), operand.begin());
}

std::pair<std::string, std::string>
split_at_first(char delim, std::string_view str)
{
	auto bndry = std::find(str.begin(), str.end(), delim);
	return std::make_pair(
		std::string(str.begin(), bndry),
		std::string(bndry == str.end() ? bndry : bndry + 1, str.end())
	);
}

OptionEqScanner::OptionEqScanner(std::string short_opt_prefix,
				 std::string long_opt_prefix,
				 std::string end_of_opts) :
	OptionScanner(std::move(short_opt_prefix), std::move(long_opt_prefix),
		      std::move(end_of_opts))
{
}

bool OptionEqScanner::is_option(const std::string& prefix, std::string_view str)
{
	return str.length() > prefix.length() &&
			starts_with(prefix, str) &&
			std::isalpha(str[prefix.length()]);
}

bool OptionEqScanner::is_long_option(std::string_view str)
{
	return is_option(m_long_opt_prefix, str);
}

bool OptionEqScanner::is_short_option(std::string_view str)
{
	return is_option(m_short_opt_prefix, str);
}

bool OptionEqScanner::scan_next(ArgumentStack& stack, std::vector<Option>& out)
{
	if (m_opt_scanning)
	{
		std::string_view next_arg = stack.top();

		if (next_arg == m_end_of_opts)
		{
			m_opt_scanning = false;
		}
		else if (is_long_option(next_arg))
		{
			next_arg.remove_prefix(m_long_opt_prefix.length());
			auto [name, value] = split_at_first(m_opt_value_delimiter, next_arg);
			out.emplace_back(name, value);
		}
		else if (is_short_option(next_arg))
		{
			next_arg.remove_prefix(m_short_opt_prefix.length());
			for (char c : next_arg)
			{
				out.emplace_back(c, "");
			}
		}
		else
		{
			return false;
		}

		stack.pop();
		return true;
	}

	return false;
}
