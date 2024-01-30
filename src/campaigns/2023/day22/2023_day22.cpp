#include "2023_day22.hpp"
#include <algorithm>

D3Position parse_3d_vector(const std::string &co_ordinates)
{
  std::vector<size_t> positions;
  std::istringstream istream(co_ordinates);
  std::string token;

  while (std::getline(istream, token, ',')) { positions.push_back(std::stoul(token)); }

  return { positions[0], positions[1], positions[2] };
}

bool overlap_2d_test(const Brick &lhs, const Brick &rhs)
{
  auto lhs_min{ lhs.min_pos };
  auto lhs_max{ lhs.max_pos };
  auto rhs_min{ rhs.min_pos };
  auto rhs_max{ rhs.max_pos };

  return (lhs_max.x_pos > rhs_min.x_pos && lhs_min.x_pos < rhs_max.x_pos
          && lhs_max.y_pos > rhs_min.y_pos && lhs_min.y_pos < rhs_max.y_pos);
}

Bricks get_bricks(const AoCLib::line_data &puzzle_data)
{
  if (puzzle_data.empty()) { return {}; }

  Bricks bricks{};
  bricks.reserve(puzzle_data.size());
  for (const auto &brick_data : puzzle_data) {
    const auto brick_corners{ AoCLib::split_string_at_delimter(brick_data, '~') };
    const auto min_corner{ brick_corners[0] };
    const auto max_corner{ brick_corners[1] };

    auto min_pos{ parse_3d_vector(min_corner) };
    auto max_pos{ parse_3d_vector(max_corner) };

    ++max_pos.x_pos, ++max_pos.y_pos, ++max_pos.z_pos;
    bricks.emplace_back(Brick{ min_pos, max_pos });
  }

  std::sort(bricks.begin(), bricks.end(), [](auto const lhs, auto const rhs) {
    return lhs.min_pos.z_pos < rhs.min_pos.z_pos;
  });

  return bricks;
}

void drop_bricks(Bricks &bricks)
{
  if (bricks.empty()) { return; }

  for (size_t index{}; index < bricks.size(); ++index) {
    auto &brick{ bricks[index] };
    if (brick.grounded) { continue; }
    size_t brick_base{ brick.min_pos.z_pos };
    bool resting{ false };
    for (size_t lower{ index }; lower > 0; --lower) {
      auto &test_brick{ bricks[lower - 1] };

      if (test_brick.max_pos.z_pos == brick_base) {// just check if the top of the test brick is
                                                   // level with the bottom of the brick
        if (overlap_2d_test(brick, test_brick)) {
          resting = true;
          brick.grounded = true;
          test_brick.supporting.push_back(index);
          brick.resting_on.push_back(lower - 1);
        }
      }
    }
    if (!resting) {
      brick.lower();
      --index;// drop the brick and repeat;
    }
  }
}

int count_smashable(Bricks &bricks)
{
  if (bricks.empty()) { return 0; }

  int smashable{};
  for (auto &brick : bricks) {
    const auto above{ brick.supports() };
    if (above == 0) {
      ++smashable;
      brick.smashable = true;
      continue;
    }
    bool possible = true;
    for (size_t index{}; index < above; ++index) {
      if (bricks[brick.supporting[index]].rests_on() == 1) {
        possible = false;
        break;
      }
    }
    if (possible) { ++smashable; 
    brick.smashable = true;}
  }

  return smashable;
}

BrickLevelIndexes index_brick_levels(const Bricks &bricks)
{
  if (bricks.empty()) { return {}; }

  BrickLevelIndexes brick_indexes(bricks.size());

  for (size_t index{}; index < bricks.size(); ++index) {
    brick_indexes[index] = BrickLevelIndex{ index, bricks[index].min_pos.z_pos, false };
  }

  std::sort(brick_indexes.begin(),
    brick_indexes.end(),
    [](const BrickLevelIndex item_1, const BrickLevelIndex item_2) {
      return std::get<1>(item_1) > std::get<1>(item_2);
    });

  return brick_indexes;
}
