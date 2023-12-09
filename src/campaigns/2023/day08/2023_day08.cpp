#include "2023_day08.hpp"

#include <limits>
#include <numeric>

Instructions create_instruction(const AoCLib::line_data &puzzle_data)
{
  Instructions instuctions{};
  if (puzzle_data.empty()) { return instuctions; }

  for (auto instruction : puzzle_data[0]) { instuctions.push(instruction); }

  return instuctions;
}

void create_network(MoveNetwork &move_network, const AoCLib::line_data &puzzle_data)
{
  move_network.clear();
  constexpr size_t key{ 0 };
  constexpr size_t l_dir{ 7 };
  constexpr size_t r_dir{ 12 };
  constexpr size_t extent{ 3 };

  if (puzzle_data.empty()) { return; }

  for (size_t index{ 2 }; index < puzzle_data.size(); ++index) {
    const std::string &line_data{ puzzle_data[index] };
    const std::string key_data(line_data, key, extent);
    const std::string left_direction(line_data, l_dir, extent);
    const std::string right_direction(line_data, r_dir, extent);
    const Move move{ key_data, Directions(left_direction, right_direction) };
    move_network.push_back(move);
  }
}

size_t make_move(Instructions &instructions,
  const MoveNetwork &move_network,
  size_t position,
  bool update_instruction)
{
  if (move_network.empty()) { return 0; }

  const char next_move = instructions.front();
  if (update_instruction) {
    instructions.pop();
    instructions.push(next_move);
  }

  auto [l_move, r_move] = move_network[position].second;
  const auto next_key = (next_move == 'L') ? l_move : r_move;
  size_t next_location{};
  for (const auto &location : move_network) {
    if (location.first == next_key) { return next_location; }
    ++next_location;
  }
  return std::numeric_limits<size_t>::max();
}

int navigate_map(Instructions &instructions, const MoveNetwork &move_network)
{
  if (move_network.empty()) { return -1; }


  int no_of_steps{ 0 };
  size_t position{};
  for (const auto &item : move_network) {
    if (item.first == "AAA") { break; }
    ++position;
  }

  while (move_network[position].first != "ZZZ") {
    position = make_move(instructions, move_network, position);
    ++no_of_steps;
  }

  return no_of_steps;
}

StartPositions get_start_postions(const AoCLib::line_data &puzzle_data)
{
  if (puzzle_data.empty()) { return StartPositions{}; }

  StartPositions start_positions{};
  for (size_t index{}; const auto &line : puzzle_data) {
    if (index < 2) {
      ++index;
      continue;
    }
    if (line[2] == 'A') { start_positions.push_back(index - 2); }
    ++index;
  }

  return start_positions;
}

int64_t follow_nodes(const AoCLib::line_data &puzzle_data)
{
  if (puzzle_data.empty()) { return 0; }

  const StartPositions map_positions{ get_start_postions(puzzle_data) };
  MoveNetwork move_network{};
  create_network(move_network, puzzle_data);
  Instructions instructions{ create_instruction(puzzle_data) };

  int64_t min_steps{1};

  for (auto position : map_positions) {
    int64_t steps{ };
    while (move_network[position].first[2] != 'Z') {
      position = make_move(instructions, move_network, position);
      ++steps;
    }
    min_steps = std::lcm(min_steps, steps);
  }

  return min_steps;
}
