#pragma once

#include <string>

struct OptionInfo
{
    OptionInfo(std::string short_opt, std::string long_opt = "",
               std::string about = "", std::string value_name = "") :
        short_opt{std::move(short_opt)},
        long_opt{std::move(long_opt)}, about{std::move(about)},
        value_name{std::move(value_name)}
    {
    }

    std::string short_opt;
    std::string long_opt;
    std::string about;
    std::string value_name;
};
