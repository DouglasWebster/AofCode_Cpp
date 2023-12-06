#pragma once

#include <string>

#include <AofCode_Cpp/aoc_library.hpp>

namespace AofCode_Cpp::cmake {
    inline constexpr std::string_view campaign_year = "2023";
    inline constexpr std::string_view campaign_day = "day05";
} //namespace AofCode::cmake


using GardenRange = std::pair<size_t, size_t>;
using Mapping = std::pair<GardenRange, GardenRange>;
using RangeMap = std::vector<Mapping>;

using Seeds = std::vector<size_t>;

/**
 * @brief create a vector of seed numbers
 * 
 * @param line a string of the form "seeds: 1 2 3 ..." 
 * @return Seeds 
 */
Seeds build_seeds_vector(const std::string &line);

/**
 * @brief build a vector of ranges for a given map 
 * 
 * @param range_vector the range map to build
 * @param data the raw data 
 * @param start_line the line on the raw data where the ranges start
 * @return int the final line of the raw data proccessed 
 */
size_t build_map(RangeMap &map, const AoCLib::line_data &data, size_t current_line);

using Catagories = std::vector<RangeMap>;

/**
 * @brief from the raw data build a vector of RangeMap 
 * 
 * @param data 
 * @return Catagories 
 */
Catagories build_catagories(const AoCLib::line_data &data);

/**
 * @brief given a seed number trace its path sequentially through the catagories
 * 
 * @param seed the number of the seed to trace
 * @param catagories a vector of RangeMap
 * @return size_t the final location of the seed
 */
size_t trace_seed(size_t seed, const Catagories &catagories);

using SourceRanges = std::vector<GardenRange>;

/**
 * @brief build a range map from the seed information of consecutive pairs <start_no, length> 
 * 
 * @param line the seed information
 * @return SourceRanges 
 */
SourceRanges build_seed_ranges(const std::string &line);

/**
 * @brief given a vector of GardenRanges construct a new RangeMap for the 
 * intersection of the sources and the next level 
 * 
 * @param source_ranges the GardenRange to build from
 * @param next_level a new RangeMap of possible GardenRanges
 * @return RangeMap 
 */
RangeMap adjust_mapping(const SourceRanges & source_ranges, const RangeMap & next_level);

using LevelRange = std::pair<size_t, Mapping>;
using LevelRanges = std::vector<LevelRange>;

/**
 * @brief create a vector of all viable ranges for each level of catagory level.
 * 
 * @param seed_ranges the initial starting ranges for the seeds
 * @param catagories the mapping for each catagory
 * @return LevelRanges 
 */
LevelRanges level_ranges(const SourceRanges &seed_ranges, const Catagories &catagories);



