#pragma once

#include <string>

#include <AofCode_Cpp/aoc_library.hpp>

namespace AofCode_Cpp::cmake {
inline constexpr std::string_view campaign_year = "2023";
inline constexpr std::string_view campaign_day = "day22";
}// namespace AofCode_Cpp::cmake

struct D3Position
{
  size_t x_pos{};
  size_t y_pos{};
  size_t z_pos{};
};

/**
 * @brief A brick has a minimum x, y, z position and a
 * maximum x, y, z, postion.  It also has a grounded state.
 * A brick is considered grounded if it resting on the ground OR another brick.
 */
class Brick
{
public:
  D3Position min_pos{};
  D3Position max_pos{};
  bool grounded{ false };
  std::vector<size_t> resting_on{};
  std::vector<size_t> supporting{};
  bool smashable{false};

  Brick(D3Position min, D3Position max) : min_pos{ min }, max_pos{ max }
  {
    grounded = (min_pos.z_pos == 1);
    resting_on.reserve(10);
    supporting.reserve(10);
  }
  void lower()
  {
    --min_pos.z_pos;
    --max_pos.z_pos;
    grounded = (min_pos.z_pos == 1);
  }

  size_t supports() const { return supporting.size(); }
  size_t rests_on() const { return resting_on.size();}
};

using Bricks = std::vector<Brick>;

/**
 * @brief Get the brick objects and store them in a vector sorted by increasing z position;
 *
 * @param puzzle_data
 * @return Bricks
 */
Bricks get_bricks(const AoCLib::line_data &puzzle_data);

/**
 * @brief drop all the bricks to their lowest levels.  i.e. all the bricks become grounded.
 *
 * @param bricks A vector of bricks that has been sorted by their z position.
 */
void drop_bricks(Bricks &bricks);

/**
 * @brief get the number of bricks that can be disintegrated.  This is effectively the
 * number of bricks that don't support a single brick.
 *
 * @param Bricks This has to have all the bricks dropped before the count occurs.
 * @return int The number of bricks that are candidates for disintegrating.
 */
int count_smashable(Bricks &bricks);


// A BrickLevelIndex encodes the index into the Bricks array, the level of that bricks base
// and if it has been visited
using BrickLevelIndex = std::tuple<size_t, size_t, bool>;
using BrickLevelIndexes = std::vector<BrickLevelIndex>;

/**
 * @brief Get the level for the base of each brick and sort them by descending value of level
 * 
 * @param bricks 
 * @return BrickLevelIndexes 
 */
BrickLevelIndexes index_brick_levels(const Bricks &bricks);