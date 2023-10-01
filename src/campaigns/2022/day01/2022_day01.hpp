#pragma once

#include <string>
#include <vector>

#include <AofCode_Cpp/aoc_library.hpp>

namespace AofCode_Cpp::cmake {
    inline constexpr std::string_view campaign_year = "2022";
    inline constexpr std::string_view campaign_day = "2022";
} //namespace AofCode::cmake

using ElvenPack = std::vector<int>;
using ElvenPacks = std::vector<ElvenPack>;
using PacksCalories= ElvenPack;

ElvenPacks collate_calories(const ElvenPacks &);

PacksCalories sum_calories(const ElvenPacks &);

int max_values(const ElvenPack &, int);