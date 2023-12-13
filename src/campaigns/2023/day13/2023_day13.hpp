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

/**
 * @brief determine if there is a horizontal line of symetry and if so where it occurs
 * after dooing one only repair;
 *  
 * @param pattern 
 * @return size_t 
 */
size_t is_repaired_horizontal_reflection(const Pattern & pattern);

/**
 * @brief determine if there is a vertical line of symetry and if so where it occurs
 * after dooing one only repair;
 *  
 * @param pattern 
 * @return size_t 
 */
size_t is_repaired_vertical_reflection(const Pattern & pattern);

/**
 * @brief return first = true if repaired and second = line of relexion;
 * 
 */
using Repair = std::pair<Axis, size_t>;

/**
 * @brief repair just one mirror in a pattern.  
 * 
 * @param pattern 
 * @return Repair 
 * 
 * @note the repair tries to repair the horizontal axis and if that fails it tries to repair on the 
 * vertical axis.
 */
Repair do_repair(const Pattern &pattern);

std::pair<size_t, size_t> do_all_repair(const Pattern & pattern);


