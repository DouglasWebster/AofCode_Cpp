#pragma once

#include <string>
#include <numeric>

#include <AofCode_Cpp/aoc_library.hpp>

namespace AofCode_Cpp::cmake {
    inline constexpr std::string_view campaign_year = "2023";
    inline constexpr std::string_view campaign_day = "day23";
} //namespace AofCode::cmake

constexpr size_t max_location{std::numeric_limits<size_t>::max()};
enum Heading {
  North = 0,
  South,
  East,
  West,
  Nowhere
};


struct Location {
    size_t North{max_location};
    size_t South{max_location};
    size_t East{max_location};
    size_t West{max_location};
    int exits{};
};

using TrailMap = std::vector<Location>;

/**
 * @brief build a graph of the trails.
 * 
 * @param puzzle_data 
 * @return TrailMap 
 * 
 * Note > prevents moving west, < prevents moving east, ^ prevents moving south
 * and v prevents moving north.
 */
TrailMap build_trails(const AoCLib::char_data data);