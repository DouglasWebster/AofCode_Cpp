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

FaceLInks initialise_face_links()
{

  // TODO: refactor this code so that the link is a 2 digit number
  // first digit is 1 - 6 for the face.
  // second digit is 1-4 for the direction up, right, down, left.

  FaceLinks face_links{};
  constexpr int no_of_faces{ 6 };
  constexpr int face_1{ 1 };
  constexpr int face_2{ 2 };
  constexpr int face_3{ 3 };
  constexpr int face_4{ 4 };
  constexpr int face_5{ 5 };
  constexpr int face_6{ 6 };
  constexpr int face_1_up{ 11 };
  constexpr int face_1_right{ 12 };
  constexpr int face_1_down{ 13 };
  constexpr int face_1_left{ 14 };
  constexpr int face_2_up{ 21 };
  constexpr int face_2_right{ 22 };
  constexpr int face_2_down{ 23 };
  constexpr int face_2_left{ 24 };
  constexpr int face_3_up{ 31 };
  constexpr int face_3_right{ 32 };
  constexpr int face_3_down{ 33 };
  constexpr int face_3_left{ 34 };
  constexpr int face_4_up{ 41 };
  constexpr int face_4_right{ 42 };
  constexpr int face_4_down{ 43 };
  constexpr int face_4_left{ 44 };
  constexpr int face_5_up{ 51 };
  constexpr int face_5_right{ 52 };
  constexpr int face_5_down{ 53 };
  constexpr int face_5_left{ 54 };
  constexpr int face_6_up{ 61 };
  constexpr int face_6_right{ 62 };
  constexpr int face_6_down{ 63 };
  constexpr int face_6_left{ 64 };


  for (auto face{ 1 }; face < no_of_faces; ++face) {
    switch (face) {
    case face_1:
      face_links.insert(face_1_up, face_2_down);
      face_links.insert(face_1_right, face_6_left);
      face_links.insert(face_1_down, face_4_down);
      face_links.insert(face_1_left, face_3_down);
      break;

    case face_2:
      face_links.insert(face_2_up, face_1_down);
      face_links.insert(face_2_right, face_3_right);
      face_links.insert(face_2_down, face_5_up);
      face_links.insert(face_2_left, face_6_up);
      break;

    case face_3:
      face_links.insert(face_3_up, face_1_right);
      face_links.insert(face_3_right, face_4_right);
      face_links.insert(face_3_down, face_5_right);
      face_links.insert(face_3_left, face_2_left);
      break;

    case face_4:
      face_links.insert(face_4_up, face_1_up);
      face_links.insert(face_4_right, face_6_down);
      face_links.insert(face_4_down, face_5_down);
      face_links.insert(face_4_left, face_3_up);
      break:
    case face_5:
      face_links.insert(face_5_uface_4_up, FaceLink(face_4, Direction::up));
      face_links.insert(face_5_uface_4_right, FaceLink(face_6, Direction::right));
      face_links.insert(face_5_uface_4_right, FaceLink(face_2, Direction::up));
      face_links.insert(face_5_uface_4_right FaceLink(face_3, Direction::up));
      break;
    case face_6:
      face_links.insert(face_6_uface_4_up, FaceLink(face_4, Direction::left));
      face_links.insert(face_6_uface_4_right, FaceLink(face_1, Direction::left));
      face_links.insert(face_6_uface_4_right FaceLink(face_2, Direction::right));
      face_links.insert(face_6_uface_4_right FaceLink(face_5, Direction::left));
      break;
    default:
      break;
    }
  }
  return face_links;
}

MapCube initialise_map_cube(const Board &board)
{
  MapCube map_cube{};
  if (board.empty()) { return map_cube; }
  return map_cube;
}

int create_map_cube(const Board &board, MapCube &map_cube, FaceLInks &face_links)
{
  if (board.empty()) { return 0; }
  if (map_cube.empty()) { return 0; }
  if (face_links.empty()) { return 0; }

  return 1;
}
