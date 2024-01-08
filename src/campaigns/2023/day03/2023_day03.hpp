#pragma once

#include <AofCode_Cpp/aoc_library.hpp>
#include <map>
#include <string>

namespace AofCode_Cpp::cmake {
inline constexpr std::string_view campaign_year = "2023";
inline constexpr std::string_view campaign_day = "day03";
}// namespace AofCode_Cpp::cmake

using Schematic = AoCLib::char_data;

/**
 * @brief a pair of numbers, the first is the number of items connected, the
 * second is the product of the connected items.
 *
 */
using PossibleGear = std::pair<int, int>;

/**
 * @brief a location of an item in the schamatic by row number then column nunber
 *
 */
using Location = std::pair<size_t, size_t>;

/**
 * @brief A map recording the position of possible gears
 *
 */
using PossibleGears = std::map<Location, PossibleGear>;

/**
 * @brief inflate the schematic by 1 one each edge with periods (.)
 *
 * @param engine the original engine scematic
 * @return Schematic the inflateds schematic
 */
Schematic inflate_schematic(const Schematic &engine);

/**
 * @brief calculates the sum of the part no's
 *
 * @param bounded_schematic a copy of the engine schematic inflated by 1 on each side
 * @param gear_map the map that records if a discovered part number could be a gear.
 * @return int
 *
 * @note The schematic is inflated by 1 on each side to make the search easier - we do not have
 * to do bounds checking provided we keep the search grid within <1 ; (max row -1)> and <1 ; max_col
 * - 1>
 */
int calculate_partno_sum(Schematic &bounded_schematic, PossibleGears &gear_map);

/**
 * @brief given a boundingin box check if there exists a symbol (anything not a digit or a period
 * (.)) within the bounding box
 *
 * @param schematic the schematic to be checked
 * @param row the row that is the basis of the box - we check the row above, this row and the next
 * row
 * @param start_col the starting column of the box
 * @param end_col the ending column of the box
 * @param gear_map the map that records if a discovered part number could be a gear.
 * @param found_value the discovered value for which we are checking if it is a part
 * @return true a symbol was found
 * @return false no symbol was found
 */
bool check_box_for_symbol(const Schematic &schematic,
  size_t row,
  size_t start_col,
  size_t end_col,
  PossibleGears &gear_map, int found_value);
