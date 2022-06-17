#include <iostream>
#include "ArgumentScanner.hpp"
#include "OptionEqScanner.hpp"

int main(int argc, char **argv)
{
	ArgumentStack stack = make_arg_stack(argc, argv);

	OptionEqScanner opt_scanner;
	ArgumentScanner scanner;
	scanner.set_option_scanner(&opt_scanner);
	ScannedArguments scanned = scanner.scan(stack);

	for (const auto& op : scanned.operands)
	{
		std::cout << "Operand: " << op << '\n';
	}

	for (const auto& op : scanned.options)
	{
		std::cout << "Option: " << op.name() << " = " << op.value() << '\n';
	}

    return 0;
}
