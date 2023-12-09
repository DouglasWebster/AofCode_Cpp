#include <chrono>
#include <iostream>
#include <numeric>

#include "2023_day08.hpp"

int main()
{
  auto time_start = std::chrono::high_resolution_clock::now();

  std::string data_file = CURRENT_LIST_DIR;
  data_file += "/input.txt";

  const AoCLib::line_data puzzle_data{ AoCLib::vectorise_line_data(data_file) };

  if (puzzle_data.empty()) {
    std::cout << "No data to analyse!  Terminating program.";
    return 0;
  }

  MoveNetwork newtwork{};
  create_network(newtwork, puzzle_data);

  Instructions instructions{create_instruction(puzzle_data)};

  const int steps{navigate_map(instructions, newtwork)};
  const int64_t min_steps{follow_nodes(puzzle_data)};

  std::cout << "Advent of Code " << AofCode_Cpp::cmake::campaign_year << " "
            << AofCode_Cpp::cmake::campaign_day << '\n';
  std::cout << "Part 1 solution: Steps required are " << steps << '\n';
  std::cout << "Part 2 solution: Minimum steps required are " << min_steps << '\n';

  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - time_start);
  std::cout << "Time taken by program: " << duration.count() << " microseconds"
            << "\n";


  return 0;
}
