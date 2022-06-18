#include <string>

#include "Option.hpp"

Option::Option(char name, std::string value) :
    m_name(1, name), m_value(std::move(value))
{
}

Option::Option(std::string name, std::string value) :
    m_name(std::move(name)), m_value(std::move(value))
{
}

const std::string& Option::name() const
{
    return m_name;
}

const std::string& Option::value() const
{
    return m_value;
}
