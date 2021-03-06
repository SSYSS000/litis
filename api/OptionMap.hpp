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

#include <map>
#include <string>
#include <vector>

template <typename AccessorT>
class OptionMap
{
public:
    OptionMap() = default;

    bool is_set(const AccessorT& id) const
    {
        return m_options.find(id) != m_options.cend();
    }

    void unset(const AccessorT& id)
    {
        m_options.erase(id);
    }

    void add(AccessorT id, std::string value)
    {
        m_options[std::move(id)].push_back(std::move(value));
    }

    void set(AccessorT id, std::string value = "")
    {
        m_options[std::move(id)] = {std::move(value)};
    }

    const std::string& get_value(const AccessorT& id) const
    {
        return m_options.at(id).back();
    }

    bool try_get_value(const AccessorT& id, std::string& value) const
    {
        try
        {
            value = this->get_value(id);
        }
        catch (const std::out_of_range& e)
        {
            return false;
        }
        return true;
    }

    std::vector<std::string> values(const AccessorT& id) const
    {
        auto it = m_options.find(id);
        if (it != m_options.cend())
        {
            return it->second;
        }
        return {};
    }

private:
    std::map<AccessorT, std::vector<std::string>> m_options;
};
