#pragma once

#include <string>

#include <AofCode_Cpp/aoc_library.hpp>

namespace AofCode_Cpp::cmake {
inline constexpr std::string_view campaign_year = "2023";
inline constexpr std::string_view campaign_day = "day14";
}// namespace AofCode_Cpp::cmake

enum class Cardinal { North, South, East, West };

using Row = std::vector<char>;
using Platform = std::vector<Row>;

/**
 * @brief Create a platform object
 *
 * @param puzzle_data
 * @return Platform
 */
Platform create_platform(const AoCLib::char_data &puzzle_data);

/**
 * @brief tilt the platform in a given direction 
 * 
 * @param platform The state of the platform before the tilt
 * @param direction the direction in which to tilt.  If no direction given it will tilt North
 * @return Platform The state of the platform after all the ball have settled.
 */
Platform tilt_platform(const Platform &platform, const Cardinal direction = Cardinal::North);

/**
 * @brief deterine the load on the support, north support by default
 * 
 * @param platform the state of the platform
 * @param support the location of the support; defaults to North if not specified.
 * @return int the load calculated for the support
 */
int64_t calculate_load(const Platform & platform, const Cardinal support = Cardinal::North);