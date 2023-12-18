#include <chrono>
#include <iostream>
#include <numeric>

#include "2023_day16.hpp"

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

  Contraption contraption{build_contraption(puzzle_data)};
  do_light_beam(contraption);

  const int total_energised{calc_max(contraption)};
  const int max_energised{find_max_tile_energisation(contraption, puzzle_data.size(), puzzle_data[0].size())};
 
  std::cout << "Advent of Code " << AofCode_Cpp::cmake::campaign_year << " "
            << AofCode_Cpp::cmake::campaign_day << '\n';
  std::cout << "Part 1 solution: Initialization sum: Total energised mirrors " << total_energised << '\n';
  std::cout << "Part 2 solution: Focusing power: Maximum energisatin level " << max_energised << '\n';

  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - time_start);
  std::cout << "Time taken by program: " << duration.count() << " microseconds"
            << "\n";


  return 0;
}
