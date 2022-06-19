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
#include <cctype>
#include <stdexcept>

#include "OptionScanner.hpp"

bool starts_with(const std::string& prefix, const std::string& operand)
{
    return operand.length() >= prefix.length() &&
           std::equal(prefix.begin(), prefix.end(), operand.begin());
}

OptionScanner::OptionScanner(std::string short_opt_prefix,
                             std::string long_opt_prefix,
                             std::string end_of_opts) :
    m_short_opt_prefix(std::move(short_opt_prefix)),
    m_long_opt_prefix(std::move(long_opt_prefix)),
    m_end_of_opts(std::move(end_of_opts))
{
    if (m_short_opt_prefix == m_long_opt_prefix)
    {
        throw std::invalid_argument("Short and long option prefixes "
                                    "may not be equal.");
    }

    if (!(m_short_opt_prefix.length() < m_long_opt_prefix.length()))
    {
        throw std::invalid_argument("Short option prefix must be shorter than "
                                    "long option prefix.");
    }
}

bool OptionScanner::is_option(const std::string& prefix, const std::string& str)
{
    return str.length() > prefix.length() && starts_with(prefix, str) &&
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
