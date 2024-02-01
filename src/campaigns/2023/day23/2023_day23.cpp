#include "2023_day23.hpp"

TrailMap build_trails(const AoCLib::char_data data)
{
  if (data.empty()) { return {}; }

  const size_t rows{ data.size() };
  const size_t cols{ data[0].size() };

  TrailMap trail_map{};
  trail_map.reserve(rows * cols);

  for (size_t row{}; row < rows; ++row) {
    for (size_t col{}; col < cols; ++col) {
      const size_t north_step = row == 0 ? max_location : (row - 1) * cols + col;
      const size_t south_step = row == rows - 1 ? max_location : (row + 1) * cols + col;
      const size_t east_step = col == cols - 1 ? max_location : row * cols + col + 1;
      const size_t west_step = col == 0 ? max_location : row * cols + col - 1;

      Location location{};
      char current_position{ data[row][col] };
      if (current_position == '#') {
        trail_map.emplace_back(location);
        continue;
      }
      switch (current_position) {
      case '^':
        location.North = north_step;
        location.exits = 1;
        break;
      case 'v':
        location.South = south_step;
        location.exits = 1;
        break;
      case '>':
        location.East = east_step;
        location.exits = 1;
        break;
      case '<':
        location.West = west_step;
        location.exits = 1;
        break;
      default:// must be a path
        int exits{};
        char n_char = (north_step == max_location) ? '#' : data[row - 1][col];
        if (n_char != '#' && n_char != 'v') {
          location.North = north_step;
          ++exits;
        }
        char s_char = (south_step == max_location) ? '#' : data[row + 1][col];
        if (s_char != '#' && s_char != '^') {
          location.South = south_step;
          ++exits;
        }
        char e_char = (east_step == max_location) ? '#' : data[row][col + 1];
        if (e_char != '#' && e_char != '<') {
          location.East = east_step;
          ++exits;
        }
        char w_char = (west_step == max_location) ? '#' : data[row][col - 1];
        if (w_char != '#' && e_char != '>') {
          location.West = west_step;
          ++exits;
        }
        location.exits = exits;
      }

      trail_map.emplace_back(location);
    }
  }
  return trail_map;
}
