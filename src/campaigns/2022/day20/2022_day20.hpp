#pragma once

#include <list>
#include <string>

#include <AofCode_Cpp/aoc_library.hpp>

namespace AofCode_Cpp::cmake {
inline constexpr std::string_view campaign_year = "2022";
inline constexpr std::string_view campaign_day = "day20";
}// namespace AofCode_Cpp::cmake

using Item = std::pair<int, bool>;
using Items = std::vector<Item>;

Items create_item_list(const AoCLib::int_data &data);

void make_moves(Items &items);
int calculate_coordinate_sum(const Items &items);
