#pragma once

#include <string>

#include <AofCode_Cpp/aoc_library.hpp>

namespace AofCode_Cpp::cmake {
    inline constexpr std::string_view campaign_year = "2023";
    inline constexpr std::string_view campaign_day = "day11";
} //namespace AofCode::cmake

using Universe = AoCLib::char_data;
/**
 * @brief A Galaxy has a number and a 2d location in the universe
 * 
 */
using Galaxy = std::pair<int, std::pair<size_t, size_t>>;
using Galaxies = std::vector<Galaxy>;
using GalaxyPair = std::pair<size_t, size_t>;
using GalaxyPairs = std::vector<GalaxyPair>;

/**
 * @brief expand the universe by increasing doubling the size of each empty row or colummm
 * 
 * @param universe 
 */
void expand_universe(Universe & universe);

/**
 * @brief Get the galaxies object
 * 
 * @param Universe 
 * @return Galaxy 
 */
Galaxies get_galaxies(const Universe &universe);

/**
 * @brief create a vector of unique pairs of galaxies
 * 
 * @param Galaxies 
 * @return GalaxyPairs 
 */
GalaxyPairs pair_galaxies(const Galaxies &galaxies);

/**
 * @brief get the total distances between galaxies using Manhattan distances
 * 
 * @param pairs 
 * @param Galaxies 
 * @return int 
 */
int calculate_galaxy_manhattan_seperation(const GalaxyPairs &pairs, const Galaxies &galaxies);

void dump_universe(const Universe &universe);


