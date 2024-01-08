#pragma once

#include <limits>
#include <numeric>
#include <stack>
#include <string>

#include <AofCode_Cpp/aoc_library.hpp>

namespace AofCode_Cpp::cmake {
inline constexpr std::string_view campaign_year = "2023";
inline constexpr std::string_view campaign_day = "day16";
}// namespace AofCode_Cpp::cmake

enum class Direction { North, South, East, West, None };

constexpr auto no_tile = std::numeric_limits<size_t>::max();

using ExitDirections = std::pair<Direction, Direction>;

struct Exit
{
  size_t tile_id{ no_tile };
  ExitDirections directions{ Direction::None, Direction::None };
};

using Exits = std::vector<Exit>;

struct Tile
{
  size_t tile_id{ no_tile };
  char tile_type{ '.' };

  // entry tile -> exit tile
  size_t n_tile{ no_tile };
  size_t s_tile{ no_tile };
  size_t e_tile{ no_tile };
  size_t w_tile{ no_tile };
  size_t void_tile{ no_tile };

  // remember how it was set up in case we need it later
  size_t n_link{ no_tile };
  size_t s_link{ no_tile };
  size_t e_link{ no_tile };
  size_t w_link{ no_tile };

  // which direction we entered from to possilbe leaving directions
  ExitDirections going_north{ Direction::North, Direction::None };
  ExitDirections going_south{ Direction::South, Direction::None };
  ExitDirections going_east{ Direction::East, Direction::None };
  ExitDirections going_west{ Direction::West, Direction::None };

  bool energised{ false };

  Exit transit_tile(Direction direction);
  size_t *match_tile_to_direction(const Direction direction);
  bool more_exits() const;
  Exit get_last_exit();
  void reset_links();
};

using Contraption = std::vector<Tile>;

/**
 * @brief given a list of tiles construct the contraption
 *
 * @param puzzle_data
 * @return Contraption
 */
Contraption build_contraption(const AoCLib::char_data &puzzle_data);

using NextMirrors = std::stack<size_t>;


/**
 * @brief send the light beam on its way from this tile, recording entry and exit conditions
 *
 * @param tile
 * @param direction the direction that the light beam enters the tile.
 * @return Exit the location of the next tile and the direction the light beam enters it.
 */
Exit transit_tile(Tile &tile, Direction direction);

/**
 * @brief traverse the path of the light beam taking accoung of all splits;
 *
 * @param contraption the item the light beam is traversing.
 * @param tile_id the starting tile for the light beam defaults top left;
 * @param direction the direction the beam is heading, defaults left to right
 */
void do_light_beam(Contraption &contraption,
  size_t tile_id = 0,
  Direction direction = Direction::East);


void draw_energised(const Contraption &contraption);

int find_max_tile_energisation(const Contraption &contraption, size_t rows, size_t cols);
int calc_max(const Contraption &contraption);