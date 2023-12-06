#pragma once

#include <string>

#include <AofCode_Cpp/aoc_library.hpp>

namespace AofCode_Cpp::cmake {
    inline constexpr std::string_view campaign_year = "2023";
    inline constexpr std::string_view campaign_day = "day06";
} //namespace AofCode::cmake


using Race = std::pair<int64_t, int64_t>;
using Races = std::vector<Race>;

/**
 * @brief Get a Races vector containing detail of each race
 * 
 * @param data the raw string of race details.
 * @return Races 
 */
Races get_races(const AoCLib::line_data &data);

/**
   * @brief given a race determine the maximum hold time of the button that still beats the previous best distance
   * 
   * @param race details of the previoius best race 
   * @return int the maximum hold time.
   */
  int64_t find_max_hold_time(const Race &race);

  /**
   * @brief given a race and a max hold time calculate the number of ways to win
   * 
   * @param race the details of the current race
   * @param max_hold_time the maximum hold time that will beat the previous best
   * @return int the number of ways you can beat the previous best.
   */
  int64_t calc_number_of_winning_ways(const Race &race, const int64_t max_hold_time);
