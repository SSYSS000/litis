#pragma once

#include <string>

/**
 * @brief Describes an option that is part of a command.
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
