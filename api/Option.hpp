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

namespace litis
{

/**
 * @brief Describes an option that is part of a command-line.
 *
 */
class Option
{
public:
    /**
     * @brief Create an Option instance from one character name and a value.
     *
     * @param name Option name. Typically short option.
     * @param value Option value.
     */
    Option(char name, std::string value);

    /**
     * @brief Create an Option instance.
     *
     * @param name Option name.
     * @param value Option value.
     */
    Option(std::string name, std::string value);

    /**
     * @brief Get the name of the option.
     *
     * @return Const reference to option name.
     */
    const std::string& name() const;

    /**
     * @brief Get the value of the option.
     *
     * @return Const reference to option value.
     */
    const std::string& value() const;

private:
    std::string m_name;
    std::string m_value;
};

} // namespace litis
