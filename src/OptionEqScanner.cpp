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

#include "OptionEqScanner.hpp"

namespace
{

std::pair<std::string, std::string> split_at_first(char delim,
                                                   const std::string& str)
{
    auto bndry = std::find(str.begin(), str.end(), delim);
    return std::make_pair(
        std::string(str.begin(), bndry),
        std::string(bndry == str.end() ? bndry : bndry + 1, str.end()));
}

} // namespace

namespace litis
{

OptionEqScanner::OptionEqScanner(std::string short_opt_prefix,
                                 std::string long_opt_prefix,
                                 std::string end_of_opts) :
    OptionScanner(std::move(short_opt_prefix), std::move(long_opt_prefix),
                  std::move(end_of_opts))
{
}

bool OptionEqScanner::scan_next(StringStack& args, std::vector<Option>& out)
{
    if (!m_opt_scanning)
    {
        return false;
    }

    std::string& arg = args.top();

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

    args.pop();
    return true;
}

} // namespace litis
