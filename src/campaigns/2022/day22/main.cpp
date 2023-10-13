#include <chrono>
#include <iostream>

#include "2022_day22.hpp"

int main()
{

  auto time_start = std::chrono::high_resolution_clock::now();

  std::string data_file = CURRENT_LIST_DIR;
  data_file += "/input.txt";

  AoCLib::char_data raw_vector{ AoCLib::vectorise_char_data(data_file) };

  if (raw_vector.empty()) {
    std::cout << "No data to analyse!  Terminating program.";
    return 0;
  }

  const Moves moves{ strip_off_moves(raw_vector) };
  const Board board(make_game_board(raw_vector));

  Location location{ get_start_position(board) };

  for (int ctr = 1; auto move : moves) {
    const int updated_position{ make_move(board, move, location) };
    update_location(updated_position, move, location);
    std::cout << "pass no: " << ctr << '\n';
    ++ctr;
   }

  constexpr int row_multiplier{ 1000 };
  constexpr int col_multiplier(4);
  constexpr int board_offset{ 1 };

  const int password = row_multiplier * (location.first.second + board_offset)
                 + col_multiplier * (location.first.first + board_offset)
                 + static_cast<int>(location.second);


  std::cout << "Advent of Code " << AofCode_Cpp::cmake::campaign_year << " "
            << AofCode_Cpp::cmake::campaign_day << '\n';
  std::cout << "Part 1 solution: Password = " << password << '\n';
  std::cout << "Part 2 solution:\n";

  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - time_start);
  std::cout << "Time taken by program: " << duration.count() << " microseconds"
            << "\n";
  return 0;
}
