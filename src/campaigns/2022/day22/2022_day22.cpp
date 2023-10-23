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

FaceLinks initialise_face_directions()
{
  FaceLinks face_links{};

  for (auto face{ 1 }; face <= no_of_faces; ++face) {
    switch (face) {
    case face_1:
      face_links.emplace(face_1_up, face_2_down);
      face_links.emplace(face_1_right, face_6_left);
      face_links.emplace(face_1_down, face_4_down);
      face_links.emplace(face_1_left, face_3_down);
      break;

    case face_2:
      face_links.emplace(face_2_up, face_1_down);
      face_links.emplace(face_2_right, face_3_right);
      face_links.emplace(face_2_down, face_5_up);
      face_links.emplace(face_2_left, face_6_up);
      break;

    case face_3:
      face_links.emplace(face_3_up, face_1_right);
      face_links.emplace(face_3_right, face_4_right);
      face_links.emplace(face_3_down, face_5_right);
      face_links.emplace(face_3_left, face_2_left);
      break;

    case face_4:
      face_links.emplace(face_4_up, face_1_up);
      face_links.emplace(face_4_right, face_6_down);
      face_links.emplace(face_4_down, face_5_down);
      face_links.emplace(face_4_left, face_3_left);
      break;

    case face_5:
      face_links.emplace(face_5_up, face_4_up);
      face_links.emplace(face_5_right, face_6_right);
      face_links.emplace(face_5_down, face_2_up);
      face_links.emplace(face_5_left, face_3_up);
      break;

    case face_6:
      face_links.emplace(face_6_up, face_4_left);
      face_links.emplace(face_6_right, face_1_left);
      face_links.emplace(face_6_down, face_2_right);
      face_links.emplace(face_6_left, face_5_left);
      break;

    default:
      break;
    }
  }
  return face_links;
}

// NOLINTBEGIN(readability-function-cognitive-complexity)
TileDirection determine_cell_on_face_change(FaceLinks &face_links,
  const TileDirection &current_tile,
  const int face_size)
{

  const int face = current_tile.first.first;
  const Direction current_heading{ current_tile.second };

  const int current_face_and_direction = face * ten + static_cast<int>(current_heading);

  auto next_face_and_direction = face_links[current_face_and_direction];
  auto next_face = next_face_and_direction / ten;
  const Direction next_heading{ static_cast<Direction>(next_face_and_direction % ten) };

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

  if (current_heading == Direction::right && next_heading == Direction::left) {
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
    next_tile.first.second.first = face_size -1;
    next_tile.first.second.second = face_size -1 - current_tile.first.second.first;
    return next_tile;
  }

  if (current_heading == Direction::right && next_heading == Direction::down) {
    next_tile.first.second.first = 0;
    next_tile.first.second.second = face_size - 1 - current_tile.first.second.first;
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

  if (current_heading == Direction::down && next_heading == Direction::right) {
    next_tile.first.second.second = 0;
    next_tile.first.second.first = face_size -1 - current_tile.first.second.second;
    return next_tile;
  }

  return next_tile;
}
// NOLINTEND(readability-function-cognitive-complexity)


MapCube initialise_map_cube(const Board &board)
{
  MapCube map_cube{};
  if (board.empty()) { return map_cube; }
  return map_cube;
}

int create_map_cube(const Board &board, const MapCube &map_cube, const FaceLinks &face_links)
{
  if (board.empty()) { return 0; }
  if (map_cube.empty()) { return 0; }
  if (face_links.empty()) { return 0; }

  return 1;
}
