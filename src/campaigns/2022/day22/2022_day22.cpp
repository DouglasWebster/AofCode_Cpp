#include "2022_day22.hpp"
#include <algorithm>
#include <string>

Moves strip_off_moves(AoCLib::char_data &raw_data)
{
  Moves moves{};

  constexpr int decade = 10;

  if (raw_data.empty()) { return moves; }

  const std::vector<char> move_data = raw_data.back();
  moves.reserve(move_data.size());
  raw_data.pop_back();
  raw_data.pop_back();

  int move_amount{};


  for (auto item : move_data) {
    if (isdigit(item) != 0) {
      move_amount = (item - '0') + decade * move_amount;
    } else {
      moves.emplace_back(std::make_pair(move_amount, static_cast<Rotation>(item)));
      move_amount = 0;
    }
  }

  moves.emplace_back(std::make_pair(move_amount, Rotation::terminate));

  return moves;
}

Board make_game_board(const AoCLib::char_data &board_data)
{
  Board game_board{};

  if (board_data.empty()) { return game_board; }

  game_board.resize(board_data.size());

  size_t max_length{};

  for (const auto &row : board_data) {
    const size_t row_length{ row.size() };
    if (row_length > max_length) { max_length = row_length; }
  }

  std::transform(board_data.begin(),
    board_data.end(),
    game_board.begin(),
    [&max_length](const std::vector<char> &board_row) {
      const std::string row(board_row.begin(), board_row.end());
      const size_t extra_needed = max_length - row.size();
      return row + std::string(extra_needed, ' ');
    });

  return game_board;
}

Location get_start_position(const Board &board)
{
  Location location{ std::make_pair(0, 0), Direction::right };

  location.first.first = static_cast<int>(board[0].find('.'));

  return location;
}

std::string extract_movement_tiles(const Board &board, const Location &location)
{

  const Direction facing = location.second;

  if (facing == Direction::right || facing == Direction::left) {
    std::string extracted_row = board[static_cast<size_t>(location.first.second)];
    if (facing == Direction::left) { std::reverse(extracted_row.begin(), extracted_row.end()); }
    return extracted_row;
  }

  std::string extracted_col(board.size(), ' ');
  const auto column = static_cast<size_t>(location.first.first);
  std::transform(
    board.begin(), board.end(), extracted_col.begin(), [column](auto row) { return row[column]; });

  if (facing == Direction::up) { std::reverse(extracted_col.begin(), extracted_col.end()); }

  return extracted_col;
}

int make_move(const Board &board, const Move &move_to, Location current_location)
{
  // get the tiles to traverse and normalise them if necessary.
  const std::string movement_tiles{ extract_movement_tiles(board, current_location) };
  const int tile_count{ static_cast<int>(movement_tiles.size()) };
  const Direction facing = current_location.second;

  int current_position = (facing == Direction::left || facing == Direction::right)
                           ? current_location.first.first// start with column no.
                           : current_location.first.second;// start with row no.

  if (facing == Direction::left || facing == Direction::up) {
    current_position = tile_count - current_position - 1;
  }

  // now do the movement.
  for (auto move_count{ move_to.first }; move_count > 0; --move_count) {
    constexpr int increase{ 1 };
    const auto next_position = (current_position == tile_count) ? 0 : current_position + increase;

    auto next_tile = movement_tiles[static_cast<size_t>(next_position)];

    if (next_tile == '.') {// it's an empty space so move onto it.
      current_position = next_position;
      ;
      continue;
    }

    if (next_tile == '#') {// it's a wall so stop moving
      break;
    }

    // no more traversable tiles, find the first traversable tile in this traverse sequence.

    std::string::size_type restart_position{};
    if (current_position == 0) {
      restart_position = movement_tiles.find_first_of(".# ");
    } else {
      restart_position = movement_tiles.find_last_of(' ', static_cast<size_t>(current_position));
      if (restart_position == std::string::npos) {
        restart_position = 0;
      } else {
        ++restart_position;
      }
    }

    auto restart_tile = movement_tiles[static_cast<size_t>(restart_position)];
    if (restart_tile == '.') {
      current_position = static_cast<int>(restart_position);
      continue;
    }

    if (restart_tile == '#') {// still can't go anywhere
      break;
    }
  }

  return (facing == Direction::down || facing == Direction::right)
           ? current_position
           : tile_count - current_position - 1;
}

void update_location(int offset, const Move &move, Location &location)
{
  const Direction facing{ location.second };

  if (facing == Direction::left || facing == Direction::right) {
    location.first.first = offset;
  } else {
    location.first.second = offset;
  }

  const Rotation turn = move.second;

  if (turn == Rotation::terminate) { return; }

  if (turn == Rotation::left) {
    switch (facing) {
    case Direction::left:
      location.second = Direction::down;
      break;
    case Direction::down:
      location.second = Direction::right;
      break;
    case Direction::right:
      location.second = Direction::up;
      break;
    case Direction::up:
      location.second = Direction::left;
      break;
    default:
      break;
    }
  } else {
    switch (facing) {
    case Direction::left:
      location.second = Direction::up;
      break;
    case Direction::up:
      location.second = Direction::right;
      break;
    case Direction::right:
      location.second = Direction::down;
      break;
    case Direction::down:
      location.second = Direction::left;
      break;
    default:
      break;
    }
  }
}

FaceLinks initialise_face_directions(const int face_size)
{
  constexpr int faces{ 7 };// the zero face is a dummy to allow faces to be referenced 1 - 6;
  constexpr int edges{ 4 };

  FaceLinks face_links(faces,
    std::vector<std::pair<int, Direction>>(edges, std::pair<int, Direction>(0, Direction::right)));

  constexpr int problem_face_size{ 50 };
  constexpr auto up = static_cast<size_t>(Direction::up);// NOLINT
  constexpr auto right = static_cast<size_t>(Direction::right);
  constexpr auto down = static_cast<size_t>(Direction::down);
  constexpr auto left = static_cast<size_t>(Direction::left);


  if (face_size != problem_face_size) {
    for (size_t face{ 1 }; face <= no_of_faces; ++face) {
      switch (face) {
      case face_1:
        face_links[face][up] = std::make_pair(face_2, Direction::down);
        face_links[face][right] = std::make_pair(face_6, Direction::left);
        face_links[face][down] = std::make_pair(face_4, Direction::down);
        face_links[face][left] = std::make_pair(face_3, Direction::down);
        break;

      case face_2:
        face_links[face][up] = std::make_pair(face_1, Direction::down);
        face_links[face][right] = std::make_pair(face_3, Direction::right);
        face_links[face][down] = std::make_pair(face_5, Direction::up);
        face_links[face][left] = std::make_pair(face_6, Direction::up);
        break;

      case face_3:
        face_links[face][up] = std::make_pair(face_1, Direction::right);
        face_links[face][right] = std::make_pair(face_4, Direction::right);
        face_links[face][down] = std::make_pair(face_5, Direction::right);
        face_links[face][left] = std::make_pair(face_2, Direction::left);
        break;

      case face_4:
        face_links[face][up] = std::make_pair(face_1, Direction::up);
        face_links[face][right] = std::make_pair(face_6, Direction::down);
        face_links[face][down] = std::make_pair(face_5, Direction::down);
        face_links[face][left] = std::make_pair(face_3, Direction::left);
        break;

      case face_5:
        face_links[face][up] = std::make_pair(face_4, Direction::up);
        face_links[face][right] = std::make_pair(face_6, Direction::right);
        face_links[face][down] = std::make_pair(face_2, Direction::up);
        face_links[face][left] = std::make_pair(face_3, Direction::up);
        break;

      case face_6:
        face_links[face][up] = std::make_pair(face_4, Direction::left);
        face_links[face][right] = std::make_pair(face_1, Direction::left);
        face_links[face][down] = std::make_pair(face_2, Direction::right);
        face_links[face][left] = std::make_pair(face_5, Direction::left);
        break;

      default:
        break;
      }
    }
  } else {
    for (size_t face{ 1 }; face <= no_of_faces; ++face) {
      switch (face) {
      case face_1:
        face_links[face][up] = std::make_pair(face_6, Direction::right);
        face_links[face][right] = std::make_pair(face_2, Direction::right);
        face_links[face][down] = std::make_pair(face_3, Direction::down);
        face_links[face][left] = std::make_pair(face_4, Direction::right);
        break;

      case face_2:
        face_links[face][up] = std::make_pair(face_6, Direction::up);
        face_links[face][right] = std::make_pair(face_5, Direction::left);
        face_links[face][down] = std::make_pair(face_3, Direction::left);
        face_links[face][left] = std::make_pair(face_1, Direction::left);
        break;

      case face_3:
        face_links[face][up] = std::make_pair(face_1, Direction::up);
        face_links[face][right] = std::make_pair(face_2, Direction::up);
        face_links[face][down] = std::make_pair(face_5, Direction::down);
        face_links[face][left] = std::make_pair(face_4, Direction::down);
        break;

      case face_4:
        face_links[face][up] = std::make_pair(face_3, Direction::right);
        face_links[face][right] = std::make_pair(face_5, Direction::right);
        face_links[face][down] = std::make_pair(face_6, Direction::down);
        face_links[face][left] = std::make_pair(face_1, Direction::right);
        break;

      case face_5:
        face_links[face][up] = std::make_pair(face_3, Direction::up);
        face_links[face][right] = std::make_pair(face_2, Direction::left);
        face_links[face][down] = std::make_pair(face_6, Direction::left);
        face_links[face][left] = std::make_pair(face_4, Direction::left);
        break;

      case face_6:
        face_links[face][up] = std::make_pair(face_4, Direction::up);
        face_links[face][right] = std::make_pair(face_5, Direction::up);
        face_links[face][down] = std::make_pair(face_2, Direction::down);
        face_links[face][left] = std::make_pair(face_1, Direction::down);
        break;

      default:
        break;
      }
    }
  }

  return face_links;
}

// NOLINTBEGIN(readability-function-cognitive-complexity)
TileDirection determine_cell_on_face_change(const FaceLinks &face_links,
  const TileDirection &current_tile,
  const int face_size)
{

  const int face = current_tile.first.first;
  const Direction current_heading{ current_tile.second };

  auto [next_face, next_heading] =
    face_links[static_cast<size_t>(face)][static_cast<size_t>(current_heading)];

  TileDirection next_tile{ { next_face, { 0, 0 } }, next_heading };

  // no change of direction so just reset the row or the column
  if (current_heading == next_heading) {
    if (current_heading == Direction::up || current_heading == Direction::down) {
      next_tile.first.second.first = (current_heading == Direction::up) ? (face_size - 1) : 0;
      next_tile.first.second.second = current_tile.first.second.second;
    } else {
      next_tile.first.second.first = current_tile.first.second.first;
      next_tile.first.second.second = (current_heading == Direction::right) ? 0 : (face_size - 1);
      return next_tile;
    }
  }
  // the change in direction is a reverse
  if ((current_heading == Direction::up && next_heading == Direction::down)
      || (current_heading == Direction::down && next_heading == Direction::up)) {
    next_tile.first.second.first = current_tile.first.second.first;
    next_tile.first.second.second = face_size - 1 - current_tile.first.second.second;
    return next_tile;
  }

  if ((current_heading == Direction::right && next_heading == Direction::left)
      || (current_heading == Direction::left && next_heading == Direction::right)) {
    next_tile.first.second.second = current_tile.first.second.second;
    next_tile.first.second.first = face_size - 1 - current_tile.first.second.first;
    return next_tile;
  }

  // finally the transitions with a twist
  if (current_heading == Direction::left && next_heading == Direction::down) {
    next_tile.first.second.first = current_tile.first.second.second;
    next_tile.first.second.second = current_tile.first.second.first;
    return next_tile;
  }

  if (current_heading == Direction::left && next_heading == Direction::up) {
    next_tile.first.second.first = face_size - 1;
    next_tile.first.second.second = face_size - 1 - current_tile.first.second.first;
    return next_tile;
  }

  if (current_heading == Direction::right && next_heading == Direction::down) {
    next_tile.first.second.first = 0;
    next_tile.first.second.second = face_size - 1 - current_tile.first.second.first;
    return next_tile;
  }

  if (current_heading == Direction::right && next_heading == Direction::up) {
    next_tile.first.second.first = face_size - 1;
    next_tile.first.second.second = current_tile.first.second.first;
    return next_tile;
  }

  if (current_heading == Direction::up && next_heading == Direction::left) {
    next_tile.first.second.second = face_size - 1;
    next_tile.first.second.first = face_size - 1 - current_tile.first.second.second;
    return next_tile;
  }

  if (current_heading == Direction::up && next_heading == Direction::right) {
    next_tile.first.second.second = 0;
    next_tile.first.second.first = current_tile.first.second.second;
    return next_tile;
  }

  if (current_heading == Direction::down && next_heading == Direction::left) {
    next_tile.first.second.second = current_tile.first.second.first;
    next_tile.first.second.first = current_tile.first.second.second;
    return next_tile;
  }

  if (current_heading == Direction::down && next_heading == Direction::right) {
    next_tile.first.second.second = 0;
    next_tile.first.second.first = face_size - 1 - current_tile.first.second.second;
    return next_tile;
  }

  return next_tile;
}
// NOLINTEND(readability-function-cognitive-complexity)

FaceOrigins determine_face_origins(const Board &board, const size_t face_size)
{
  if (board.empty() || face_size == 0) { return FaceOrigins{}; }

  const size_t board_x_extent{ board[0].size() };
  const size_t board_y_extent{ board.size() };

  FaceOrigins face_origins{};
  int face{ 1 };
  for (size_t y_offset{ 0 }; y_offset < board_y_extent; y_offset += face_size) {
    for (size_t x_offset{ 0 }; x_offset < board_x_extent; x_offset += face_size) {
      if (board[y_offset][x_offset] == ' ') { continue; }
      face_origins[face] = { static_cast<int>(y_offset), static_cast<int>(x_offset) };
      face++;
    }
  }

  return face_origins;
}

MapCube initialise_map_cube(const Board &board, const size_t face_size)
{
  if (board.empty() || face_size == 0) { return MapCube{}; }

  const size_t board_x_sections{ board[0].size() / face_size };
  const size_t board_y_sections{ board.size() / face_size };

  MapCube map_cube{};
  for (size_t section_row{ 0 }; section_row < board_y_sections; ++section_row) {
    std::vector<std::vector<char>> face_data{};
    for (size_t section_column{ 0 }; section_column < board_x_sections; ++section_column) {
      for (size_t row{ 0 }; row < face_size; ++row) {
        const size_t board_row = section_row * face_size + row;
        std::vector<std::string> row_parts{ AoCLib::split_string_into_chunks(
          board[board_row], face_size) };

        if (row_parts[section_column][0] == ' ') { break; }// it's a filler section so ignore it

        const std::vector<char> row_data(
          row_parts[section_column].begin(), row_parts[section_column].end());
        face_data.push_back(row_data);
      }
      if (face_data.empty()) { continue; }// must have been a filler section so don't keep it.
      map_cube.push_back(face_data);
      face_data.clear();
    }
  }

  return map_cube;
}

bool make_3d_move(const MapCube &map_cube, TileDirection &tile, const FaceLinks &face_links)
{

  if (map_cube.empty()) { return false; }

  const int face_size{ static_cast<int>(map_cube[0].size()) };
  const Direction direction{ tile.second };
  size_t face{ static_cast<size_t>(tile.first.first)
               - 1 };// tile.face is 1 based, we need it zero based.
  int y_position{ tile.first.second.first };
  int x_position{ tile.first.second.second };

  switch (direction) {
  case Direction::up:
    y_position--;
    break;
  case Direction::down:
    y_position++;
    break;
  case Direction::left:
    x_position--;
    break;
  case Direction::right:
    x_position++;
    break;
  default:
    break;
  }

  TileDirection next_tile_direction{};
  if (y_position < 0 || y_position == face_size || x_position < 0 || x_position == face_size) {
    next_tile_direction = determine_cell_on_face_change(face_links, tile, face_size);
    y_position = next_tile_direction.first.second.first;
    x_position = next_tile_direction.first.second.second;
    face = static_cast<size_t>(next_tile_direction.first.first - 1);
  } else {
    next_tile_direction = tile;
    next_tile_direction.first.second.first = y_position;
    next_tile_direction.first.second.second = x_position;
  }

  if (map_cube[face][static_cast<size_t>(y_position)][static_cast<size_t>(x_position)] == '#') {
    return false;// can't move so keep the current location
  }

  tile = next_tile_direction;
  return true;
}

TileDirection do_3d_moves(const Moves &moves, const MapCube &map_cube, const FaceLinks &face_links)
{

  TileDirection current_position{ { 1, { 0, 0 } }, Direction::right };

  for (auto move : moves) {
    int steps{ move.first };
    while (steps > 0) {
      make_3d_move(map_cube, current_position, face_links);
      --steps;
    }

    const Direction facing{ current_position.second };

    const Rotation turn = move.second;

    if (turn == Rotation::terminate) {
      return current_position;// all done, just return where we are.
    }

    if (turn == Rotation::left) {
      switch (facing) {
      case Direction::left:
        current_position.second = Direction::down;
        break;
      case Direction::down:
        current_position.second = Direction::right;
        break;
      case Direction::right:
        current_position.second = Direction::up;
        break;
      case Direction::up:
        current_position.second = Direction::left;
        break;
      default:
        break;
      }
    } else {
      switch (facing) {
      case Direction::left:
        current_position.second = Direction::up;
        break;
      case Direction::up:
        current_position.second = Direction::right;
        break;
      case Direction::right:
        current_position.second = Direction::down;
        break;
      case Direction::down:
        current_position.second = Direction::left;
        break;
      default:
        break;
      }
    }
  }

  return TileDirection{};// we shouldn't get here so if we do return an empty TileDirection!
}

int calculate_3d_password(const TileDirection &tile, FaceOrigins &face_origins)
{
  int password{ -1 };
  if (tile.first.first == 0) { return password; }
  const auto face_origin = face_origins[tile.first.first];//

  const int y_offset{ face_origin.first + tile.first.second.first + 1 };
  const int x_offset{ face_origin.second + tile.first.second.second + 1 };
  const int direction_value{ static_cast<int>(tile.second) };

  constexpr int y_multiplier{ 1000 };
  constexpr int x_multiplier{ 4 };

  password = y_offset * y_multiplier + x_offset * x_multiplier + direction_value;
  return password;
}
