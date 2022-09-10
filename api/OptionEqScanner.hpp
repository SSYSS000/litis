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

#include <string>
#include <vector>

#include "Option.hpp"
#include "OptionScanner.hpp"

namespace litis
{

/**
 * @brief OptionScanner that scans options whose values
 *        are part of the same argument, e.g. "--option=value".
 *
 */
class OptionEqScanner : public OptionScanner
{
public:
    /**
     * @brief Create an OptionEqScanner instance.
     *
     * @param short_opt_prefix Prefix of a short option.
     * @param long_opt_prefix Prefix of a long option.
     * @param end_of_opts Option scanning stops at this mark.
     */
    OptionEqScanner(std::string short_opt_prefix = "-",
                    std::string long_opt_prefix  = "--",
                    std::string end_of_opts      = "--");

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
    char m_opt_value_delimiter = '=';
};

} // namespace litis
