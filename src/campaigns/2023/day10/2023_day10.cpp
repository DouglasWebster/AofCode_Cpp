#include "2023_day10.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
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

Location find_start(const AoCLib::char_data &data)
{
  if (data.empty()) {
    return { std::numeric_limits<size_t>::max(), std::numeric_limits<size_t>::max() };
  }

  size_t col_pos{};
  size_t row_pos{};
  for (const auto &row : data) {
    for (const auto col : row) {
      if (col == 'S') { return Location{ row_pos, col_pos }; }
      ++col_pos;
    }
    ++row_pos;
    col_pos = 0;
  }
  return { std::numeric_limits<size_t>::max(), std::numeric_limits<size_t>::max() };
}

// NOLINTBEGIN(readability-function-cognitive-complexity)
Pipe start_direction(const AoCLib::char_data &data, const Location &start_location)
{
  if (data.empty()) { return {Connection::Ground, Connection::Ground}; }

  Connection first_connection{Connection::Ground};
  Connection second_connection{Connection::Ground};

  auto [row, col] = start_location;
  if (row > 0) {
    const char next{ data[row - 1][col] };
    if (next == 'F' || next == '7' || next == '|') { 
      if(first_connection == Connection::Ground) {first_connection = Connection::North;}
      else{second_connection = Connection::North;}
     }
  }
  if (row < data.size() - 1) {
    const char next{ data[row + 1][col] };
    if (next == 'L' || next == 'J' || next == '|') {  
      if(first_connection == Connection::Ground) {first_connection = Connection::South;}
      else{second_connection = Connection::South;} }
  }
  if (col > 0) {
    const char next{ data[row][col - 1] };
    if (next == 'L' || next == 'F' || next == '-') {  
      if(first_connection == Connection::Ground) {first_connection = Connection::West;}
      else{second_connection = Connection::West;} }
  }
  if (col < data[0].size() - 1) {
    const char next{ data[row][col + 1] };
    if (next == '7' || next == 'J' || next == '-') {  
      if(first_connection == Connection::Ground) {first_connection = Connection::East;}
      else{second_connection = Connection::East;} }
  }

  return {first_connection, second_connection};
}
// NOLINTEND(readability-function-cognitive-complexity)

void correct_start_symbol(const Location &start, const Pipe &pipe, AoCLib::char_data &data){
    char replacement_char{};
    
    switch (pipe.first)
    {
    case Connection::North:
      replacement_char = (pipe.second == Connection::East) ? 'L' : 'J';
      break;
    case Connection::South:
      replacement_char = (pipe.second == Connection::East) ? 'F' : '7';
      break;
    case Connection::East:
      replacement_char = (pipe.second == Connection::North) ? 'J' : '7';
      break;
    case Connection::West:
      replacement_char = (pipe.second == Connection::North) ? 'L' : 'F';
      break;
    default:
      break;
    }

    data[start.first][start.second] = replacement_char;
}

AoCLib::char_data
  draw_map(const Location start, const Pipe &connections, const AoCLib::char_data &data)
{

  if (data.empty()) { return AoCLib::char_data{}; }
  const auto max_size{ std::numeric_limits<size_t>::max() };
  AoCLib::char_data path_map(data.size(), std::vector<char>(data[0].size(), '.'));
  correct_start_symbol(start, connections, path_map);
  Location next{ max_size, max_size };
  bool first_iteration{ true };
  Connection direction{connections.first};

  while (next != start) {
    if (first_iteration) {
      next = start;
      first_iteration = false;
    }

    switch (direction) {
    case Connection::West:
      --next.second;
      ;
      break;
    case Connection::East:
      ++next.second;
      ;
      break;
    case Connection::South:
      ++next.first;
      ;
      break;
    case Connection::North:
      --next.first;
      ;
      break;
    default:
      break;
    }

    auto next_char{ data[next.first][next.second] };
    if(next_char == 'S') {next_char = path_map[next.first][next.second];}
    path_map[next.first][next.second] = next_char;
    switch (next_char) {
    case 'J':
      direction = (direction == Connection::East) ? Connection::North : Connection::West;
      break;
    case 'F':
      direction = (direction == Connection::West) ? Connection::South : Connection::East;
      break;
    case 'L':
      direction = (direction == Connection::West) ? Connection::North : Connection::East;
      break;
    case '7':
      direction = (direction == Connection::East) ? Connection::South : Connection::West;
      break;
    default:
      break;
    }
  }

  print_map(data, "paths.txt");
  print_map(path_map, "corrected_start.txt");
  return path_map;
}

// NOLINTBEGIN(readability-function-cognitive-complexity)
int count_enclosed(const AoCLib::char_data &data)
{
  AoCLib::char_data working_set = data;
  if (data.empty()) { return 0; }
  int total{};

  auto flip_boolean{ [](bool &item) {
    if (item) { item = false; } // NOLINT
    else {item = true;}
  } };

  for (auto &row : working_set) {
    row.push_back(' ');
    bool inside = false; // NOLINT

    for (size_t index{}; index < row.size() - 1; ++index) {
      const auto first_char{ row[index] };
      if (inside && first_char == '.') {
        row[index] = 'I';
        ++total;
        continue;
      }
      if (first_char == '|') {
        flip_boolean(inside);
        continue;
      }
      auto next_char{ row[index + 1] };

      while(next_char == '-') { // eat up the horizontal path segments
        ++index;
        next_char = row[index+1];
      }

      switch (first_char) {
      case 'L':
        if (next_char == '7') { flip_boolean(inside); }
        ++index;
        break;
      case 'F':
        if (next_char == 'J') { flip_boolean(inside); }
        ++index;
        break;
      case 'J':
        if (next_char == 'F') { flip_boolean(inside); }
        ++index;
        break;
      case '7':
        if (next_char == 'L') { flip_boolean(inside); }
        ++index;
        break;
      default:
        break;
      }
    }
  }
  print_map(working_set, "enclosed_marked.txt");
  return total;
}
// NOLINTEND(readability-function-cognitive-complexity)

void print_map(const AoCLib::char_data &data, const std::string &file_name)
{
  std::string data_file = CURRENT_LIST_DIR;
  data_file += "/" + file_name;

  std::ofstream file_dump;
  file_dump.open(data_file, std::ofstream::out | std::ofstream::trunc);
  for (const auto &row : data) {
    for (const auto col : row) { file_dump << col; }
    file_dump << '\n';
  }
  file_dump << '\n';
  file_dump.close();
}


size_t count_steps(const MapData &map_data)//, LocationTypes &locations)
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
