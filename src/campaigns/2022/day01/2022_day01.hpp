#pragma once

#include <string>
#include <vector>

namespace AofCode_Cpp::cmake {
    inline constexpr std::string_view campaign_year = "2022";
    inline constexpr std::string_view campaign_day = "2022";
} //namespace AofCode::cmake

using ElvenPacks = std::vector<std::vector<int>>;

std::vector<int> collate_calories(const ElvenPacks & elven_packs);