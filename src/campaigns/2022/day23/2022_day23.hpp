#pragma once

#include <string>

#include <AofCode_Cpp/aoc_library.hpp>

namespace AofCode_Cpp::cmake {
inline constexpr std::string_view campaign_year = "2022";
inline constexpr std::string_view campaign_day = "day23";
}// namespace AofCode_Cpp::cmake

using Vector2dPosition = std::pair<size_t, size_t>;
using GroveSize = std::pair<size_t, size_t>;
using GroveExtent = std::pair<Vector2dPosition, GroveSize>;
using GroveMap = std::vector<std::vector<char>>;

enum class Direction { north = 1, south = 2, west = 4, east = 8, stay_put = 15};

/**
 * @brief given a grove map reduce it to its smallest rectangle
 *
 * @param grove_map the map to be reduced
 * 
 * The Grove extent consist of a Vector2dPosition and a GroveSize.  
 * Vector2dPosition is the <row, col> coordinat of the start of the smallest rectangel that contains all the elves.  
 * GroveSize is the <row, col> extent of the rectangle that contains all the elves.
 */
GroveExtent get_map_extent(const GroveMap &grove_map);

/**
 * @brief Create a next map object
 *
 * @param current_map the current state of the grove map
 * @return GroveMap an new inflated grove map ready for the next round
 *
 * @note The new map is a copy of the old map reduced to it's minimum size then
 * inflated by one row or column around each edge.
 */
GroveMap create_next_map(const GroveMap &current_map);

using MovementMap = std::vector<std::vector<Direction>>;
/**
 * @brief mark a map with positons that can be moved to and elves that can move
 *
 * @param map
 * @param first_direction the initail direction to search in
 * @return GroveMap - a map marked up with the direction each elf **wants** to move in
 *
 * The original map is marked in the following way
 * 1. 'N' - an elf that doesn't need to move as it has spaces all around.
 * 2. '#' - an elf that can move if there is an available space
 * 3. 'A' - an available space that has been reserved by an elf
 * 4. 'B' - a space that could be claimed by more that one elf so is blocked.
 * 5. '.' - a normal space that is unreserved.
 */
MovementMap mark_allowable_positions(GroveMap &map,const Direction first_direction);

/**
 * @brief given a map and a location return the allowable move directions
 * 
 * @param map the current state of the grove
 * @param location the current location of the elf that wants to move
 * @return int - the allowable move directions.
 * 
 * The allowable move directions are determined by adding together the Direction enum.  
 * A value of 15 indicates all directions are available and 
 * a zero value indicates that no direction is available.
 * 
 * @note This only takes account of squares which are currently occupied by elves; all other squares are treated as available.
 */
unsigned int which_directions(const GroveMap & map, const Vector2dPosition & location);

/**
 * @brief moves the elves to their new positions
 * 
 * @param GroveMap the location of the elves and available positions
 * @param movement_map the desired movement direction for each elve that can move.
 * 
 * For each desired movement in the movement map it moves the corresponding elve if the desired position is free.
 * After all movements have been carried out it resets the grove map so that all spaces not occupied by an elve is
 * marked as free.
 */
void do_movement(GroveMap & grove_map, const MovementMap & movement_map);

/**
 * @brief count the empty ground in the grove map
 * 
 * @param grove_map 
 * @return int The number of spaces in the smallest orthogonal rectangle that contains all the elves
 */
int count_empty_ground(const GroveMap & grove_map);