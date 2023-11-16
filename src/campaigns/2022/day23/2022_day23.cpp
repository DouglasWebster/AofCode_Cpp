#include "2022_day23.hpp"

#include <algorithm>
#include <array>
#include <ranges>

GroveExtent get_map_extent(const GroveMap &grove_map)
{
  GroveExtent grove_extent{ Vector2dPosition(0, 0), GroveSize(0, 0) };
  if (grove_map.empty()) { return grove_extent; }

  grove_extent.second.second = grove_map.size();
  grove_extent.first.first = grove_map[0].size();


  // decrease the y size by 1 for each empty line at the end.
  // for (auto grove_iterator = grove_map.rbegin(); grove_iterator != grove_map.rend();
  // ++grove_iterator) {
  for (const auto &grove_iterator : std::ranges::reverse_view(grove_map)) {
    const auto row_iterator = find(grove_iterator.begin(), grove_iterator.end(), '#');
    if (row_iterator != grove_iterator.end()) { break; }
    grove_extent.second.second--;
  }

  // decrease the y size by 1 and increase the y start position by 1 for each empty line.

  for (auto grove_row : grove_map) {
    std::vector<char>::iterator row_iterator;
    row_iterator = find(grove_row.begin(), grove_row.end(), '#');
    if (row_iterator != grove_row.end()) { break; }

    grove_extent.second.second--;
    grove_extent.first.second++;
  }

  auto row_index{ grove_extent.first.second };
  auto row_end_index{ row_index + grove_extent.second.second };
  for (; row_index < row_end_index; ++row_index) {
    const auto &grove_row{ grove_map[row_index] };
    auto first_plant_iterator = std::find(grove_row.begin(), grove_row.end(), '#');
    if (first_plant_iterator != grove_row.end()) {
      auto first_plant_position =
        static_cast<size_t>(std::distance(grove_row.begin(), first_plant_iterator));
      if (first_plant_position < grove_extent.first.first) {
        grove_extent.first.first = first_plant_position;
      }
    }
  }

  row_index = grove_extent.first.second;
  for (; row_index < row_end_index; ++row_index) {
    const auto &grove_row{ grove_map[row_index] };
    std::array<char, 1> plant = { '#' };
    auto last_plant_iterator =
      std::find_end(grove_row.begin(), grove_row.end(), plant.begin(), plant.end());
    if (last_plant_iterator != grove_row.end()) {
      auto row_x_extent = static_cast<size_t>(std::distance(grove_row.begin(), last_plant_iterator))
                          - grove_extent.first.first + 1;

      if (row_x_extent > grove_extent.second.first) { grove_extent.second.first = row_x_extent; }
    }
  }
  return grove_extent;
}

GroveMap create_next_map(const GroveMap &current_map)
{
  if (current_map.empty()) { return GroveMap{}; }

  const GroveExtent current_map_extent{ get_map_extent(current_map) };

  const auto current_map_row_extent{ current_map_extent.second.second };
  const auto current_map_col_extent{ current_map_extent.second.first };

  GroveMap next_map(current_map_row_extent + 2, std::vector<char>(current_map_col_extent + 2, ' '));

  auto current_map_row_start{ current_map_extent.first.second };
  auto current_map_col_start{ current_map_extent.first.first };
  const auto current_map_row_end{ current_map_row_start + current_map_row_extent };
  const auto current_map_col_end{ current_map_col_start + current_map_col_extent };
  size_t new_row{ 1 };
  for (auto current_row{ current_map_col_start }; current_row < current_map_row_end;
       current_row++) {
    size_t new_col{ 1 };
    for (auto current_col{ current_map_col_start }; current_col < current_map_col_end;
         current_col++) {
      next_map[new_row][new_col] = current_map[current_col][current_col];
      ++new_col;
    }
    ++new_row;
  }
  return next_map;
}

void mark_allowable_positions(GroveMap &map, Direction first_direction)
{
  if (map.empty()) { return; }
  if (first_direction == Direction::north) { return; }
}

int which_directions(const GroveMap &map, const Vector2dPosition &location)
{
  if (map.empty()) { return 0; }
  if (map[location.first][location.second] != '#') {return 0;}

  int available_directions{ 0 };
  Vector2dPosition cell_1{};
  Vector2dPosition cell_2{};
  Vector2dPosition cell_3{};

  // check north;
  cell_1 = { location.first - 1, location.second - 1 };
  cell_2 = { location.first - 1, location.second };
  cell_3 = { location.first - 1, location.second + 1 };
  if (map[cell_1.first][cell_1.second] != '#' && map[cell_2.first][cell_2.second] != '#'
      && map[cell_3.first][cell_3.second] != '#') {
    available_directions += static_cast<int> (Direction::north);
  }

  // check east;
  cell_1 = { location.first - 1, location.second + 1 };
  cell_2 = { location.first , location.second + 1 };
  cell_3 = { location.first + 1, location.second + 1 };
  if (map[cell_1.first][cell_1.second] != '#' && map[cell_2.first][cell_2.second] != '#'
      && map[cell_3.first][cell_3.second] != '#') {
    available_directions += static_cast<int> (Direction::east);
  }

  // check south;
  cell_1 = { location.first + 1, location.second - 1 };
  cell_2 = { location.first + 1, location.second };
  cell_3 = { location.first + 1, location.second + 1 };
  if (map[cell_1.first][cell_1.second] != '#' && map[cell_2.first][cell_2.second] != '#'
      && map[cell_3.first][cell_3.second] != '#') {
    available_directions += static_cast<int> (Direction::south);
  }

  // check west;
  cell_1 = { location.first - 1, location.second - 1 };
  cell_2 = { location.first , location.second - 1 };
  cell_3 = { location.first + 1, location.second -1 };
  if (map[cell_1.first][cell_1.second] != '#' && map[cell_2.first][cell_2.second] != '#'
      && map[cell_3.first][cell_3.second] != '#') {
    available_directions += static_cast<int> (Direction::west);
  }

  return available_directions;
}
