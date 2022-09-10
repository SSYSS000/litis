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

namespace litis
{

/**
 * @brief A map for accessing option values.
 *
 */
template <typename KeyType>
class OptionMap
{
public:
    /**
     * @brief Construct an empty OptionMap.
     *
     */
    OptionMap() = default;

    /**
     * @brief Check if an option is set.
     *
     * @param key Option key.
     * @return bool True if set, false otherwise.
     */
    bool is_set(const KeyType& key) const
    {
        return m_options.find(key) != m_options.cend();
    }

    /**
     * @brief Unset an option, deleting it from this map.
     *
     * @param key Option key.
     */
    void unset(const KeyType& key)
    {
        m_options.erase(key);
    }

    /**
     * @brief Add a value to an option.
     *
     * @param key Option key.
     * @param value New option value.
     */
    void add(KeyType key, std::string value)
    {
        m_options[std::move(key)].push_back(std::move(value));
    }

    /**
     * @brief Set the sole value of an option.
     *
     * @param key Option key.
     * @param value New option value.
     */
    void set(KeyType key, std::string value)
    {
        m_options[std::move(key)] = {std::move(value)};
    }

    /**
     * @brief Get the latest value assigned to an option.
     *
     * @param key Option key.
     * @return Option value.
     */
    const std::string& get_value(const KeyType& key) const
    {
        return m_options.at(key).back();
    }

    /**
     * @brief Try to get the value of an option with get_value().
     *
     * @param key Option key.
     * @param value Location to store the value at.
     * @return bool True if value was available and stored, false otherwise.
     */
    bool try_get_value(const KeyType& key, std::string& value) const
    {
        try
        {
            value = this->get_value(key);
        }
        catch (const std::out_of_range& e)
        {
            return false;
        }
        return true;
    }

    /**
     * @brief Get all values assigned to an option.
     *
     * @param key Option key.
     * @return Values assigned to option.
     */
    std::vector<std::string> values(const KeyType& key) const
    {
        auto it = m_options.find(key);
        if (it != m_options.cend())
        {
            return it->second;
        }
        return {};
    }

private:
    std::map<KeyType, std::vector<std::string>> m_options;
};

} // namespace litis
