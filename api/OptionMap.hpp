
#pragma once

#include <map>
#include <vector>
#include <string>

template<typename AccessorT>
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
