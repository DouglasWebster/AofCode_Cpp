#pragma once

#include <list>
#include <string>

#include <AofCode_Cpp/aoc_library.hpp>

namespace AofCode_Cpp::cmake {
inline constexpr std::string_view campaign_year = "2022";
inline constexpr std::string_view campaign_day = "day20";
}// namespace AofCode_Cpp::cmake

using Item = std::pair<int64_t, bool>;
using Items = std::vector<Item>;

using Locations = std::vector<int>;

Items create_item_list(const AoCLib::int_data &data);

void make_moves(Items &items);
int64_t calculate_coordinate_sum(const Items &items);
