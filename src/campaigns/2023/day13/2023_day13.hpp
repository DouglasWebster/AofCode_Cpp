#pragma once

#include <string>

#include <AofCode_Cpp/aoc_library.hpp>

namespace AofCode_Cpp::cmake {
    inline constexpr std::string_view campaign_year = "2023";
    inline constexpr std::string_view campaign_day = "day13";
} //namespace AofCode::cmake

enum class Axis {
    Vertical,
    Horizontal
};

using Mirrors = std::string;
using Pattern = std::vector<std::string>;
using Patterns = std::vector<Pattern>;

/**
 * @brief Get the patterns object
 * 
 * @param puzzle_data 
 * @return Patterns 
 */
Patterns get_patterns (const AoCLib::str_data &puzzle_data);

/**
 * @brief determine if there is a horizontal line of symetry and if so where it occurs
 * 
 * @param pattern 
 * @return int 0 if no line of symetry
 */
size_t is_horizontal_reflection(const Pattern &pattern);

/**
 * @brief determine if there is a vertical line of symetry and if so where it occurs
 * 
 * @param pattern 
 * @return int 0 if no line of symetry
 */
size_t is_vertical_reflection(const Pattern &pattern);



