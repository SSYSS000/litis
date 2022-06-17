#include <cassert>
#include "OptionScanner.hpp"

OptionScanner::OptionScanner(std::string short_opt_prefix, std::string long_opt_prefix, std::string end_of_opts) :
	m_short_opt_prefix(std::move(short_opt_prefix)),
	m_long_opt_prefix(std::move(long_opt_prefix)),
	m_end_of_opts(std::move(end_of_opts))
{
	assert(m_short_opt_prefix.length() < m_long_opt_prefix.length());
}
