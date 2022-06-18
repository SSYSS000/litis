#include <algorithm>
#include <string>

#include "OptionEqScanner.hpp"

std::pair<std::string, std::string> split_at_first(char delim,
                                                   const std::string& str)
{
    auto bndry = std::find(str.begin(), str.end(), delim);
    return std::make_pair(
        std::string(str.begin(), bndry),
        std::string(bndry == str.end() ? bndry : bndry + 1, str.end()));
}

OptionEqScanner::OptionEqScanner(std::string short_opt_prefix,
                                 std::string long_opt_prefix,
                                 std::string end_of_opts) :
    OptionScanner(std::move(short_opt_prefix), std::move(long_opt_prefix),
                  std::move(end_of_opts))
{
}

bool OptionEqScanner::scan_next(ArgumentStack& stack, std::vector<Option>& out)
{
    if (!m_opt_scanning)
    {
        return false;
    }

    std::string& arg = stack.top();

    if (arg == m_end_of_opts)
    {
        m_opt_scanning = false;
    }
    else if (is_long_option(arg))
    {
        arg.erase(0, m_long_opt_prefix.length());
        auto [name, value] = split_at_first(m_opt_value_delimiter, arg);
        out.emplace_back(std::move(name), std::move(value));
    }
    else if (is_short_option(arg))
    {
        arg.erase(0, m_short_opt_prefix.length());
        for (char c : arg)
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
