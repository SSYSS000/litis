#include <algorithm>
#include <string>

#include "OptionSpScanner.hpp"

OptionSpScanner::OptionSpScanner(std::string short_opt_prefix,
                                 std::string long_opt_prefix,
                                 std::string end_of_opts) :
    OptionScanner(std::move(short_opt_prefix), std::move(long_opt_prefix),
                  std::move(end_of_opts))
{
}

void OptionSpScanner::expect_value(std::string option_no_pfx)
{
    m_value_opts.insert(std::move(option_no_pfx));
}

bool OptionSpScanner::is_value_expected(char option_no_pfx) const
{
    return is_value_expected(std::string(1, option_no_pfx));
}

bool OptionSpScanner::is_value_expected(const std::string& option_no_pfx) const
{
    return m_value_opts.find(option_no_pfx) != m_value_opts.cend();
}

bool OptionSpScanner::scan_next(ArgumentStack& stack, std::vector<Option>& out)
{
    if (!m_opt_scanning)
    {
        return false;
    }

    std::string arg = std::move(stack.top());
    stack.pop();

    if (arg == m_end_of_opts)
    {
        m_opt_scanning = false;
    }
    else if (is_long_option(arg))
    {
        arg.erase(0, m_long_opt_prefix.length());
        if (!stack.empty() && is_value_expected(arg))
        {
            out.emplace_back(std::move(arg), std::move(stack.top()));
            stack.pop();
        }
        else
        {
            out.emplace_back(std::move(arg), "");
        }
    }
    else if (is_short_option(arg))
    {
        arg.erase(0, m_short_opt_prefix.length());

        for (auto it = arg.begin(); it != arg.end() - 1; ++it)
        {
            out.emplace_back(*it, "");
        }

        if (!stack.empty() && is_value_expected(arg.back()))
        {
            out.emplace_back(arg.back(), std::move(stack.top()));
            stack.pop();
        }
        else
        {
            out.emplace_back(arg.back(), "");
        }
    }
    else
    {
        // Put the argument back on the stack.
        stack.push(std::move(arg));
        return false;
    }

    return true;
}
