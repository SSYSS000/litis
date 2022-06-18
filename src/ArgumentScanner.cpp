#include <vector>

#include "ArgumentScanner.hpp"
#include "ArgumentStack.hpp"
#include "Option.hpp"
#include "OptionScanner.hpp"

ArgumentScanner::ArgumentScanner(OptionScanner* opt_scanner) :
    m_opt_scanner(opt_scanner)
{
}

void ArgumentScanner::set_option_scanner(OptionScanner* opt_scanner)
{
    m_opt_scanner = opt_scanner;
}

ScannedArguments ArgumentScanner::scan(ArgumentStack& stack)
{
    ScannedArguments scanned;

    // Loop through all the arguments.
    while (!stack.empty())
    {
        if (m_opt_scanner && m_opt_scanner->scan_next(stack, scanned.options))
            ; // Option scanner handled this argument.
        else
        {
            scanned.operands.emplace_back(stack.top());
            stack.pop();
        }
    }

    return scanned;
}
