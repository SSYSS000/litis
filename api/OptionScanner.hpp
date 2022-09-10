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

#include <optional>
#include <string>

#include "Option.hpp"
#include "StringStack.hpp"

namespace litis
{

/**
 * @brief A base class for option scanners.
 *
 */
class OptionScanner
{
public:
    /**
     * @brief Construct an option scanner.
     *
     * @param short_opt_prefix Short option prefix.
     * @param long_opt_prefix Long option prefix.
     * @param end_of_opts No more options are expected after this string.
     */
    OptionScanner(std::string short_opt_prefix, std::string long_opt_prefix,
                  std::string end_of_opts);

    /**
     * @brief Destruct this OptionScanner.
     */
    virtual ~OptionScanner() = default;

    /**
     * @brief Scan the next argument and store it in out if it's an option.
     *
     * @param args Command-line arguments.
     * @param out Scanned options are appended to this vector.
     * @return bool True if the argument was recognized and handled, false if
     * not.
     */
    virtual bool scan_next(StringStack& args, std::vector<Option>& out) = 0;

protected:
    /**
     * @brief Check if a string is prefixed by prefix.
     *
     * @param prefix String prefix.
     * @param str A string.
     * @return bool True if prefix exists, false if not.
     */
    bool is_option(const std::string& prefix, const std::string& str);

    /**
     * @brief Check if a string is a long option.
     *
     * @param str A string.
     * @return bool True if long option, false otherwise.
     */
    bool is_long_option(const std::string& str);

    /**
     * @brief Check if a string is a short option.
     *
     * @param str A string.
     * @return bool True if short option, false otherwise.
     */
    bool is_short_option(const std::string& str);

    bool m_opt_scanning = true;
    std::string m_short_opt_prefix;
    std::string m_long_opt_prefix;
    std::string m_end_of_opts;
};

} // namespace litis
