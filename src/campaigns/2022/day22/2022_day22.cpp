#include "2022_day22.hpp"
#include <algorithm>

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

  for (const auto &row : game_board) {
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

Location make_move(const Board &board, const Move &move_to, Location current_location)
{

  const Location location{};

  const int x_size{ static_cast<int>(board[0].size()) };
  // const int y_size{static_cast<int>(board.size())};

  int x_position{ current_location.first.first };
  const int y_position{ current_location.first.second };
  const Direction direction = current_location.second;

  for (auto move_count{ move_to.first }; move_count > 0; --move_count) {
    if (direction == Direction::right || direction == Direction::left) {
      const int offset = (direction == Direction::right) ? 1 : -1;
      const std::string &row = board[static_cast<size_t>(y_position)];
      const int next_position = x_position + offset;

      if (row[static_cast<size_t>(next_position)] == '.') {// it's an empty space so continue moving
        x_position += offset;
        continue;
      }

      if (row[static_cast<size_t>(next_position)] == '#') {// it;s a wall so stop moving
        break;
      }
      // no more board so find the current row boundary!!
      const int backtrack_offset = offset * -1;
      int backtrack_position = x_position;
      while (backtrack_position >= 0 && backtrack_position <= x_size) {
        backtrack_position += backtrack_offset;
        if (row[static_cast<size_t>(backtrack_position)] == ' ') { break; }
      }
      if (row[static_cast<size_t>(backtrack_position)] == '#') {// still no good
        break;
      }

      x_position = backtrack_position;//
    } else {
    }
  }

  return location;
}
