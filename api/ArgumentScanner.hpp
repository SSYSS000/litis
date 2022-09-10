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

namespace litis
{

class OptionScanner;

/**
 * @brief Stores scanned option arguments as Option class instances and
 *        non-option arguments as plain strings.
 *
 */
struct ScannedArguments
{
    /*
     * Contains everything but the options and their values.
     * The first string in the vector is the first non-option argument, which
     * is typically the program executable name.
     */
    std::vector<std::string> operands;

    /*
     * Contains all options recognized by an option scanner.
     */
    std::vector<Option> options;
};

/**
 * @brief Responsible for scanning command-line arguments.
 *
 */
class ArgumentScanner
{
public:
    /**
     * @brief Create an ArgumentScanner instance.
     *
     * @param opt_scanner Scanner used to scan command-line options.
     */
    ArgumentScanner(OptionScanner* opt_scanner = nullptr);

    /**
     * @brief Set the scanner used to scan command-line options.
     *
     * @param opt_scanner Scanner used to scan command-line options.
     */
    void set_option_scanner(OptionScanner* opt_scanner);

    /**
     * @brief Scan command-line arguments.
     *
     * @param argc Number of command-line arguments.
     * @param argv Command-line argument array.
     * @return ScannedArguments The results of the scan.
     */
    ScannedArguments scan(int argc, const char* const* argv);

private:
    OptionScanner* m_opt_scanner;
};

} // namespace litis
