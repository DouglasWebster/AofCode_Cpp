#pragma once

#include <string>

#include <AofCode_Cpp/aoc_library.hpp>

namespace AofCode_Cpp::cmake {
    inline constexpr std::string_view campaign_year = "2023";
    inline constexpr std::string_view campaign_day = "day12";
} //namespace AofCode::cmake

using DamagedGroups = std::vector<size_t>;
/**
 * @brief A list of springs which are either in and unknown condition " ? ", broken " # " or working " . "
 * 
 */
using Springs = std::string;

int first_item_fits(const Springs & springs, const DamagedGroups &groups);