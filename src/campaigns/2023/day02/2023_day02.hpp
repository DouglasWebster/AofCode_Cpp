#pragma once

#include <string>

#include <AofCode_Cpp/aoc_library.hpp>

namespace AofCode_Cpp::cmake {
    inline constexpr std::string_view campaign_year = "2023";
    inline constexpr std::string_view campaign_day = "day02";
} //namespace AofCode::cmake

enum class Cube {
    red,
    green,
    blue
};

using CubeSet = std::pair<Cube, int>;
using Reveal = std::vector<CubeSet>;
using Reveals = std::vector<Reveal>;

struct Game {
    int game_no{};
    Reveals reveals{};
    int min_blue{};
    int min_green{};
    int min_red{};
};

using Games = std::vector<Game>;

/**
 * @brief build the games vector from the raw data
 * 
 * @param raw_data a vector of vector of strings.
 * @return GAMES 
 * 
 * @note The raw data is a 2d vector, each row of represents a game.  The row is a vector of two strings;
 * the first string being the game number, the second string the reveals in that game.
 */
Games build_games(const AoCLib::line_data &raw_data);

/**
 * @brief count the possible games
 * 
 * @param Games a vector of games
 * @return int accumulation of of the game no for impossible games
 */
int count_possible_games(const Games & games);

/**
 * @brief calculate the sum of the game power sets
 * 
 * @param games a vector of games
 * @return int the sum of each games power which is the multiple of the minimum cubes of each colour.
 */
int sum_set_powers(const Games & games);

