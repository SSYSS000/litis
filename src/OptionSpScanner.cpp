/*
 * BSD 3-Clause License
 *
 * Copyright (c) 2022, Jesse Hörkkö (SSYSS000)
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#include <algorithm>
#include <string>

#include "OptionSpScanner.hpp"

namespace litis
{

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

bool OptionSpScanner::scan_next(StringStack& args, std::vector<Option>& out)
{
    if (!m_opt_scanning)
    {
        return false;
    }

    std::string arg = std::move(args.top());
    args.pop();

    if (arg == m_end_of_opts)
    {
        m_opt_scanning = false;
    }
    else if (is_long_option(arg))
    {
        arg.erase(0, m_long_opt_prefix.length());
        if (!args.empty() && is_value_expected(arg))
        {
            out.emplace_back(std::move(arg), std::move(args.top()));
            args.pop();
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

        if (!args.empty() && is_value_expected(arg.back()))
        {
            out.emplace_back(arg.back(), std::move(args.top()));
            args.pop();
        }
        else
        {
            out.emplace_back(arg.back(), "");
        }
    }
    else
    {
        // Put the argument back on the stack.
        args.push(std::move(arg));
        return false;
    }

    return true;
}

} // namespace litis
