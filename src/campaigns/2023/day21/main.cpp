#include <chrono>
#include <iostream>

#include "2023_day21.hpp"

int main()
{

  auto time_start = std::chrono::high_resolution_clock::now();

  std::string data_file = CURRENT_LIST_DIR;
  data_file += "/input.txt";

  const AoCLib::char_data puzzle_data{ AoCLib::vectorise_char_data(data_file) };

  if (puzzle_data.empty()) {
    std::cout << "No data to analyse!  Terminating program.";
    return 0;
  }
  Garden garden{ create_garden(puzzle_data) };

  size_t start_pos{};
  for (; start_pos < garden.size(); ++start_pos) {
    if (garden[start_pos].type == 'S') { break; }
  }

  Possibles possibles{ start_pos };
  constexpr int moves{64};
  for (int move{}; move < moves; ++move) { make_move(possibles, garden); }

  std::cout << "Advent of Code " << AofCode_Cpp::cmake::campaign_year << " "
            << AofCode_Cpp::cmake::campaign_day << '\n';
  std::cout << "Part 1 solution: Reachable plots = " << possibles.size() << '\n';
  std::cout << "Part 2 solution:\n";

  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - time_start);
  std::cout << "Time taken by program: " << duration.count() << " microseconds"
            << "\n";

  return 0;
}
