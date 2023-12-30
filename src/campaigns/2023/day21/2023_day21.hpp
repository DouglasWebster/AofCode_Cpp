#pragma once

#include <string>
#include <limits>
#include <unordered_set>

#include <AofCode_Cpp/aoc_library.hpp>

namespace AofCode_Cpp::cmake {
    inline constexpr std::string_view campaign_year = "2023";
    inline constexpr std::string_view campaign_day = "day21";
} //namespace AofCode::cmake

constexpr size_t max_location{std::numeric_limits<size_t>::max()};

struct Tile {
    size_t location{max_location};
    size_t north{max_location};
    size_t south{max_location};
    size_t east{max_location};
    size_t west{max_location};
    char type{'.'};
};

using Garden = std::vector<Tile>;

Garden create_garden(const AoCLib::char_data & data);

// A set containing the locations after a step.  This
// This includes any rocks which will be in the location 'max_location'
using Possibles = std::unordered_set<size_t>;

/**
 * @brief Given a set of locations move one in each cardinal
 * direction storing the location storing the new moves in
 * a unordered map
 * 
 * @param possible an unordered map of current locations.  This is
 * updated to reflect the new possible locations. 
 * @param garden the map on which the step is to be taken.
 */
void make_move(Possibles &possibles, const Garden &garden);