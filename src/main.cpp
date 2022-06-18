#include <iostream>
#include "ArgumentScanner.hpp"
#include "OptionEqScanner.hpp"
#include "OptionSpScanner.hpp"
#include "OptionMap.hpp"
#include "OptionInfo.hpp"

constexpr auto SHORT_OPT_PREFIX = "-";
constexpr auto LONG_OPT_PREFIX = "--";
constexpr auto END_OF_OPTS = "--";

enum class MyOpt
{
	ADDRESS,
	RETRY,
	QUIT,
	VERBOSITY,
	HELP,
	VERSION
};

std::map<MyOpt, OptionInfo> opt_info {
		{MyOpt::ADDRESS, 		OptionInfo("a", "address", "the address to send to", "address")},
		{MyOpt::RETRY, 			OptionInfo("r", "retry", "retry this many times", "retry_count")},
		{MyOpt::QUIT, 			OptionInfo("q", "", "quit the app")},
		{MyOpt::VERBOSITY, 		OptionInfo("v", "", "set verbosity level")},
		{MyOpt::HELP,			OptionInfo("h", "help", "show help text")},
		{MyOpt::VERSION,		OptionInfo("", "version", "show version")}
};

OptionMap<MyOpt> options_to_map(const std::vector<Option>& options)
{
	OptionMap<MyOpt> map;
	for (const auto& o : options)
	{
		for (const auto& [id, info] : opt_info)
		{
			if (o.name() == info.short_opt || o.name() == info.long_opt)
			{
				map.add(id, o.value());
			}
		}
	}
	return map;
}

OptionMap<MyOpt> just_give_me_the_damn_map(int argc, char **argv)
{
	ArgumentStack stack = make_arg_stack(argc, argv);

	OptionSpScanner opt_scanner(SHORT_OPT_PREFIX, LONG_OPT_PREFIX, END_OF_OPTS);

	for(const auto& [id, info] : opt_info)
	{
		if (!info.value_name.empty())
		{
			opt_scanner.expect_value(info.short_opt);
			opt_scanner.expect_value(info.long_opt);
		}
	}

	ArgumentScanner scanner(&opt_scanner);
	ScannedArguments scanned = scanner.scan(stack);

	return options_to_map(scanned.options);
}

int main(int argc, char **argv)
{
	auto opt_map = just_give_me_the_damn_map(argc, argv);
	std::cout << "verbosity: " << opt_map.values(MyOpt::VERBOSITY).size() << '\n';
	std::cout << "retry: " << opt_map.get_value(MyOpt::RETRY) << '\n';

    return 0;
}
