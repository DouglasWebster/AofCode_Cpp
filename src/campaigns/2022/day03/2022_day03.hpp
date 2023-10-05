#pragma once

#include <string>

#include <AofCode_Cpp/aoc_library.hpp>

namespace AofCode_Cpp::cmake {
    inline constexpr std::string_view campaign_year = "2022";
    inline constexpr std::string_view campaign_day = "day03";
} //namespace AofCode::cmake

using Rucksack = std::pair<std::string, std::string>;
using Rucksacks = std::vector<Rucksack>;
using Contents = std::vector<std::string>;

Contents collate_contents(const AoCLib::str_data &);
Rucksack get_compartments(const std::string &);
char find_common_item(const Rucksack &);
int calculate_priority(const char item);
int calculate_badges(const Contents &);

