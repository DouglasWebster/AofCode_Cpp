#pragma once

#include <string>

#include <AofCode_Cpp/aoc_library.hpp>

namespace AofCode_Cpp::cmake {
    inline constexpr std::string_view campaign_year = "2022";
    inline constexpr std::string_view campaign_day = "day04";
} //namespace AofCode::cmake

using Section = std::pair<int, int>;
using Assignment = std::pair<Section, Section>;
using Assignments = std::vector <Assignment>;

Assignments collate_assignments(const AoCLib::str_data &);
bool contains_fully(const Assignment &);
bool overlapping(const Assignment &);
