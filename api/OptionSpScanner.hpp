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
#pragma once

#include <set>
#include <string>
#include <vector>

#include "OptionScanner.hpp"
#include "StringStack.hpp"

namespace litis
{

class Option;

/**
 * @brief OptionScanner that scans options whose values
 *        can be separated by whitespace, e.g. "--option value".
 *
 */
class OptionSpScanner : public OptionScanner
{
public:
    /**
     * @brief Construct an OptionSpScanner.
     *
     * @param short_opt_prefix Short option prefix.
     * @param long_opt_prefix Long option prefix.
     * @param end_of_opts No more options are expected after this string.
     */
    OptionSpScanner(std::string short_opt_prefix = "-",
                    std::string long_opt_prefix  = "--",
                    std::string end_of_opts      = "--");

    /**
     * @brief Set an option to expect a value.
     *
     * @param option_no_pfx Option without its prefix string.
     */
    void expect_value(std::string option_no_pfx);

    /**
     * @brief Scan the next argument and store it in out if it's an option.
     *
     * @param args Command-line arguments.
     * @param out Scanned options are appended to this vector.
     * @return bool True if the argument was recognized and handled, false if
     * not.
     */
    bool scan_next(StringStack& args, std::vector<Option>& out) override;

private:
    /**
     * @brief Check if an option expects a value.
     *
     * @param option_no_pfx Option without its prefix string.
     * @return bool True if value expected, false otherwise.
     */
    bool is_value_expected(char option_no_pfx) const;

    /**
     * @brief Check if an option expects a value.
     *
     * @param option_no_pfx Option without its prefix string.
     * @return bool True if value expected, false otherwise.
     */
    bool is_value_expected(const std::string& option_no_pfx) const;

    std::set<std::string> m_value_opts;
};

} // namespace litis
