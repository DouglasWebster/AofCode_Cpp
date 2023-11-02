#pragma once

#include <list>
#include <string>
#include <tuple>


#include <AofCode_Cpp/aoc_library.hpp>

namespace AofCode_Cpp::cmake {
inline constexpr std::string_view campaign_year = "2022";
inline constexpr std::string_view campaign_day = "day20";
}// namespace AofCode_Cpp::cmake

using OriginalPosition = size_t;
using Value = int64_t;
using Item = std::pair<Value, OriginalPosition>;
using Items = std::vector<Item>;

using CurrentPosition = size_t;
using Locations = std::vector<CurrentPosition>;


auto create_item_vectors(const AoCLib::int_data &data) -> std::tuple<Items, Locations>;

void make_moves(Items &items, Locations &Locations);
Value calculate_coordinate_sum(const Items &items);


void apply_decryption_key (Items & items, int64_t key);
