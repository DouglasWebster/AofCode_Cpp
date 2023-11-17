#include "2022_day23.hpp"

#include <algorithm>
#include <array>
#include <ranges>

GroveExtent get_map_extent(const GroveMap &grove_map)
{
  GroveExtent grove_extent{ Vector2dPosition(0, 0), GroveSize(0, 0) };
  if (grove_map.empty()) { return grove_extent; }

  grove_extent.second.first = grove_map.size();
  grove_extent.first.second = grove_map[0].size();


  // decrease the row size by 1 for each empty line at the end.
  for (const auto &grove_iterator : std::ranges::reverse_view(grove_map)) {
    const auto row_iterator = find(grove_iterator.begin(), grove_iterator.end(), '#');
    if (row_iterator != grove_iterator.end()) { break; }
    grove_extent.second.first--;
  }

  // decrease the row size by 1 and increase the row start position by 1 for each empty line.

  for (auto grove_row : grove_map) {
    std::vector<char>::iterator row_iterator;
    row_iterator = find(grove_row.begin(), grove_row.end(), '#');
    if (row_iterator != grove_row.end()) { break; }

    grove_extent.second.first--;
    grove_extent.first.first++;
  }

  // scan the rows for the least column position that has a plant
  auto row_index{ grove_extent.first.first };
  auto row_end_index{ row_index + grove_extent.second.first };
  for (; row_index < row_end_index; ++row_index) {
    const auto &grove_row{ grove_map[row_index] };
    auto first_plant_iterator = std::find(grove_row.begin(), grove_row.end(), '#');
    if (first_plant_iterator != grove_row.end()) {
      auto first_plant_position =
        static_cast<size_t>(std::distance(grove_row.begin(), first_plant_iterator));
      if (first_plant_position < grove_extent.first.second) {
        grove_extent.first.second = first_plant_position;
      }
    }
  }

  // scan the rows for the maximum column postion that has a plant and use it to set the column size
  row_index = grove_extent.first.first;
  for (; row_index < row_end_index; ++row_index) {
    const auto &grove_row{ grove_map[row_index] };
    std::array<char, 1> plant = { '#' };
    auto last_plant_iterator =
      std::find_end(grove_row.begin(), grove_row.end(), plant.begin(), plant.end());
    if (last_plant_iterator != grove_row.end()) {
      auto col_extent = static_cast<size_t>(std::distance(grove_row.begin(), last_plant_iterator))
                        - grove_extent.first.second + 1;

      if (col_extent > grove_extent.second.second) { grove_extent.second.second = col_extent; }
    }
  }
  return grove_extent;
}

GroveMap create_next_map(const GroveMap &current_map)
{
  if (current_map.empty()) { return GroveMap{}; }

  const GroveExtent current_map_extent{ get_map_extent(current_map) };

  const auto current_map_row_extent{ current_map_extent.second.first };
  const auto current_map_col_extent{ current_map_extent.second.second };

  GroveMap next_map(current_map_row_extent + 2, std::vector<char>(current_map_col_extent + 2, '.'));

  const auto current_map_row_start{ current_map_extent.first.first };
  const auto current_map_col_start{ current_map_extent.first.second };
  for (size_t row_offset{ 0 }; row_offset < current_map_row_extent; row_offset++) {
    for (size_t col_offset{ 0 }; col_offset < current_map_col_extent; col_offset++) {
      next_map[row_offset + 1][col_offset + 1] =
        current_map[current_map_row_start + row_offset][current_map_col_start + col_offset];
    }
  }
  return next_map;
}

//  NOLINTBEGIN(readability-function-cognitive-complexity)
MovementMap mark_allowable_positions(GroveMap &map, const Direction first_direction)
{
  if (map.empty()) { MovementMap{}; }

  MovementMap movement_map(map[0].size(), std::vector<Direction>(map.size(), Direction::stay_put));
  constexpr unsigned int no_match{ 0 };

  const size_t last_row_position{ map.size() - 1 };
  const size_t last_col_position(map[0].size() - 1);

  for (size_t row_position{ 1 }; row_position < last_row_position; row_position++) {
    for (size_t col_position{ 1 }; col_position < last_col_position; col_position++) {
      auto desired_direction{ first_direction };
      if (map[row_position][col_position] != '#') { continue; }

      const auto available_directions{ which_directions(map, { row_position, col_position }) };

      if (available_directions == static_cast<unsigned int>(Direction::stay_put)) {
        map[row_position][col_position] = 'N';
        continue;
      }

      for (int counter{ 0 }; counter < 4; ++counter) {// limit it to four tries.

        if ((static_cast<unsigned int>(desired_direction) & available_directions) != no_match) {
          movement_map[row_position][col_position] = desired_direction;
          switch (desired_direction) {
          case Direction::north:
            map[row_position - 1][col_position] =
              (map[row_position - 1][col_position] == '.') ? 'A' : 'B';
            break;
          case Direction::south:
            map[row_position + 1][col_position] =
              (map[row_position + 1][col_position] == '.') ? 'A' : 'B';
            break;
          case Direction::west:
            map[row_position][col_position - 1] =
              (map[row_position][col_position - 1] == '.') ? 'A' : 'B';
            break;
          case Direction::east:
            map[row_position][col_position + 1] =
              (map[row_position][col_position + 1] == '.') ? 'A' : 'B';
            break;
          default:
            break;
          }
          break;
        }

        // move on to the next direction to try.
        switch (desired_direction) {
        case Direction::north:
          desired_direction = Direction::south;
          break;
        case Direction::south:
          desired_direction = Direction::west;
          break;
        case Direction::west:
          desired_direction = Direction::east;
          break;
        case Direction::east:
          desired_direction = Direction::north;
          break;
        default:
          break;
        }
      }
    }
  }
  return movement_map;
}
//  NOLINTEND(readability-function-cognitive-complexity)

unsigned int which_directions(const GroveMap &map, const Vector2dPosition &location)
{
  if (map.empty()) { return 0; }
  if (map[location.first][location.second] != '#') { return 0; }

  unsigned int available_directions{ 0 };
  Vector2dPosition cell_1{};
  Vector2dPosition cell_2{};
  Vector2dPosition cell_3{};

  // check north;
  cell_1 = { location.first - 1, location.second - 1 };
  cell_2 = { location.first - 1, location.second };
  cell_3 = { location.first - 1, location.second + 1 };
  if (map[cell_1.first][cell_1.second] != '#' && map[cell_2.first][cell_2.second] != '#'
      && map[cell_3.first][cell_3.second] != '#') {
    available_directions += static_cast<unsigned int>(Direction::north);
  }

  // check east;
  cell_1 = { location.first - 1, location.second + 1 };
  cell_2 = { location.first, location.second + 1 };
  cell_3 = { location.first + 1, location.second + 1 };
  if (map[cell_1.first][cell_1.second] != '#' && map[cell_2.first][cell_2.second] != '#'
      && map[cell_3.first][cell_3.second] != '#') {
    available_directions += static_cast<unsigned int>(Direction::east);
  }

  // check south;
  cell_1 = { location.first + 1, location.second - 1 };
  cell_2 = { location.first + 1, location.second };
  cell_3 = { location.first + 1, location.second + 1 };
  if (map[cell_1.first][cell_1.second] != '#' && map[cell_2.first][cell_2.second] != '#'
      && map[cell_3.first][cell_3.second] != '#') {
    available_directions += static_cast<unsigned int>(Direction::south);
  }

  // check west;
  cell_1 = { location.first - 1, location.second - 1 };
  cell_2 = { location.first, location.second - 1 };
  cell_3 = { location.first + 1, location.second - 1 };
  if (map[cell_1.first][cell_1.second] != '#' && map[cell_2.first][cell_2.second] != '#'
      && map[cell_3.first][cell_3.second] != '#') {
    available_directions += static_cast<unsigned int>(Direction::west);
  }

  return available_directions;
}

//  NOLINTBEGIN(readability-function-cognitive-complexity)
void do_movement(GroveMap &grove_map, const MovementMap &movement_map)
{
  if (grove_map.empty() || movement_map.empty()) { return; }

  const size_t last_movement_col{ movement_map[0].size() - 1 };
  const size_t last_movement_row{ movement_map.size() - 1 };

  for (size_t movement_row{ 1 }; movement_row < last_movement_row; movement_row++) {
    for (size_t movement_col{ 1 }; movement_col < last_movement_col; movement_col++) {
      if (movement_map[movement_row][movement_col] == Direction::stay_put) { continue; }

      switch (movement_map[movement_row][movement_col]) {
      case Direction::north:
        if (grove_map[movement_row - 1][movement_col] == 'A') {
          grove_map[movement_row - 1][movement_col] = '#';
          grove_map[movement_row][movement_col] = '.';
        }
        break;
      case Direction::south:
        if (grove_map[movement_row + 1][movement_col] == 'A') {
          grove_map[movement_row + 1][movement_col] = '#';
          grove_map[movement_row][movement_col] = '.';
        }
        break;
      case Direction::east:
        if (grove_map[movement_row][movement_col + 1] == 'A') {
          grove_map[movement_row][movement_col + 1] = '#';
          grove_map[movement_row][movement_col] = '.';
        }
        break;
      case Direction::west:
        if (grove_map[movement_row][movement_col - 1] == 'A') {
          grove_map[movement_row][movement_col - 1] = '#';
          grove_map[movement_row][movement_col] = '.';
        }
        break;

      default:
        break;
      }
    }
  }

  for (auto &row : grove_map) {
    for (auto &item : row) {
      if (item == 'N') { item = '#'; }
      if (item != '#') { item = '.'; }
    }
  }
}
//  NOLINTEND(readability-function-cognitive-complexity)

int count_empty_ground(const GroveMap &grove_map)
{
  const GroveExtent search_area{ get_map_extent(grove_map) };

  int space_count{ 0 };
  const auto row_start{ search_area.first.second };
  const auto row_size{ search_area.second.second };
  const auto col_start{ search_area.first.first };
  const auto col_size{ search_area.second.first };

  for (size_t row_offset{ 0 }; row_offset < row_size; ++row_offset) {
    for (size_t col_offset{ 0 }; col_offset < col_size; ++col_offset) {
      if (grove_map[row_start + row_offset][col_start + col_offset] == '.') { ++space_count; }
    }
  }

  return space_count;
}
