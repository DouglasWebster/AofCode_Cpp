#include "2023_day10.hpp"
#include <limits>

MapData build_map_data(const AoCLib::char_data &puzzle_data, LocationTypes &locations)
{
  if (puzzle_data.empty()) { return MapData{}; }
  const size_t rows{ puzzle_data[0].size() };
  const size_t cols{ puzzle_data.size() };

  const Pipe no_pipe{ Connection::Ground, Connection::Ground };

  Sketch pipes(rows, std::vector<Pipe>(cols, no_pipe));
  Location start_position{};

  for (size_t row{}; const auto &row_data : puzzle_data) {
    for (size_t col{}; const auto &data : row_data) {
      Pipe pipe;
      switch (data) {
      case ConnectionType::Vertical:
        pipe = Pipe{ Connection::North, Connection::South };
        break;
      case ConnectionType::Horizontal:
        pipe = Pipe{ Connection::West, Connection::East };
        break;
      case ConnectionType::NorthEast:
        pipe = Pipe{ Connection::North, Connection::East };
        break;
      case ConnectionType::NorthWest:
        pipe = Pipe{ Connection::North, Connection::West };
        break;
      case ConnectionType::SouthEast:
        pipe = Pipe{ Connection::South, Connection::East };
        break;
      case ConnectionType::SouthWetst:
        pipe = Pipe{ Connection::South, Connection::West };
        break;
      case ConnectionType::Ground:
        pipe = Pipe{ Connection::Ground, Connection::Ground };
        break;
      case ConnectionType::Start:
        pipe = Pipe{ Connection::Start, Connection::Start };
        start_position = Location{ row, col };
        break;
      default:
        break;
      }
      pipes[row][col] = pipe;
      if (pipe.first != Connection::Ground) { locations[row][col] = GroundType::Ground; }
      ++col;
    }
    ++row;
  }
  auto [start_row, start_col] = start_position;
  auto next_row = start_row == (rows - 1) ? rows - 1 : start_row + 1;
  auto prev_row = start_row == 0 ? 0 : start_row - 1;
  auto next_col = start_col == (cols - 1) ? cols - 1 : start_col + 1;
  auto prev_col = start_col == 0 ? 0 : start_col - 1;

  const Connection north_con = pipes[prev_row][start_col].first;
  if (north_con == Connection::South) { pipes[start_row][start_col].first = Connection::North; }
  const Connection south_con = pipes[next_row][start_col].first;
  if (south_con == Connection::North) { pipes[start_row][start_col].first = Connection::South; }
  const Connection west_con = pipes[start_row][prev_col].second;
  if (west_con == Connection::East) { pipes[start_row][start_col].second = Connection::West; }
  const Connection east_con = pipes[start_row][next_col].second;
  if (east_con == Connection::West) { pipes[start_row][start_col].second = Connection::East; }

  return MapData{ start_position, pipes };
}

LocationTypes set_locations(const AoCLib::char_data &puzzle_data)
{
  if (puzzle_data.empty()) { return LocationTypes{}; }

  const auto rows = puzzle_data.size();
  const auto cols = puzzle_data[0].size();

  LocationTypes locations{ rows, std::vector<GroundType>(cols, GroundType::Pipe) };

  for (size_t row_index{}; row_index < rows; ++row_index) {
    for (size_t col_index{}; col_index < cols; ++col_index) {
      if (puzzle_data[row_index][col_index] == '.') {
        locations[row_index][col_index] = GroundType::Ground;
      }
    }
  }

  return locations;
}

size_t count_inner_tiles(const LocationTypes &locations)
{
  if (locations.empty()) { return 0; }

  // size_t inner_tiles{};

  // for (auto const row : locations) {
  //   for (const auto col : row) {
  //     // TODO: fill in the code for finding the loop internals.
  //   }
  // }
  return 0;
}


size_t count_steps(const MapData &map_data)  //, LocationTypes &locations)
{
  if (map_data.second.empty()) { return size_t{}; }

  size_t steps{};

  const Location start_positition{ map_data.first };
  Location next_location{ start_positition };
  const Sketch sketch = map_data.second;
  Connection next_direction{ sketch[start_positition.first][start_positition.second].first };

  do {// NOLINT
    Connection entry_connection{ Connection::Ground };
    switch (next_direction) {
    case Connection::North:
      --next_location.first;
      entry_connection = Connection::South;
      break;
    case Connection::South:
      ++next_location.first;
      entry_connection = Connection::North;
      break;
    case Connection::West:
      --next_location.second;
      entry_connection = Connection::East;
      break;
    case Connection::East:
      ++next_location.second;
      entry_connection = Connection::West;
      break;
    default:
      break;
    }

    auto [connection_1, connection_2] = sketch[next_location.first][next_location.second];
    next_direction = (entry_connection == connection_1) ? connection_2 : connection_1;

    ++steps;
  } while (next_location != start_positition);

  return steps;
}
