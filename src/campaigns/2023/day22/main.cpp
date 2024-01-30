#include <chrono>
#include <iostream>

#include "2023_day22.hpp"

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

  auto bricks{ get_bricks(puzzle_data) };
  drop_bricks(bricks);
  for (const auto &brick : bricks) {
    if(brick.grounded == false) {
        std::cout << "A non grounded brick found\n";
    }
  }
  const auto smashable{ count_smashable(bricks) };

  std::cout << "Advent of Code " << AofCode_Cpp::cmake::campaign_year << " "
            << AofCode_Cpp::cmake::campaign_day << '\n';
  std::cout << "Part 1 solution: Bricks that could be chosen: " <<smashable << '\n';
  std::cout << "Part 2 solution:\n";

  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - time_start);
  std::cout << "Time taken by program: " << duration.count() << " microseconds"
            << "\n";

  return 0;
}
