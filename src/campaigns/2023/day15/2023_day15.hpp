#pragma once

#include <string>
#include <list>

#include <AofCode_Cpp/aoc_library.hpp>

namespace AofCode_Cpp::cmake {
    inline constexpr std::string_view campaign_year = "2023";
    inline constexpr std::string_view campaign_day = "day15";
} //namespace AofCode::cmake

using Step = std::string;
using Sequence = std::vector<Step>;

using Lens = std::pair<std::string, int>;
using Box = std::list<Lens>;
using HashMap = std::vector<Box>;


/**
 * @brief for a give Step return the hashed value;
 * 
 * @param step 
 * @return int 
 */
size_t hash_step(const Step & step);

/**
 * @brief Create a hashmap object
 * 
 * @param puzzle_data 
 * @return HashMap 
 */
HashMap create_hashmap(const AoCLib::line_data &puzzle_data);

/**
 * @brief calcuate the focusing power of all the lenses in th HASHMAP
 * 
 * @param hash_map 
 * @return int64_t 
 */
size_t calc_focusing_power(const HashMap &hash_map);

