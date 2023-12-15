#include <chrono>
#include <iostream>
#include <numeric>

#include "2023_day15.hpp"

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

  const Sequence sequence{AoCLib::split_string_at_delimter(puzzle_data[0], ',')};

  size_t total{};
  for (const auto &step : sequence) {
    total += hash_step(step);
  }

  const HashMap hash_map{create_hashmap(puzzle_data)};
  const size_t focusing_power{calc_focusing_power(hash_map)};
 
  std::cout << "Advent of Code " << AofCode_Cpp::cmake::campaign_year << " "
            << AofCode_Cpp::cmake::campaign_day << '\n';
  std::cout << "Part 1 solution: Initialization sum: " << total << '\n';
  std::cout << "Part 2 solution: Focusing power: " << focusing_power << '\n';

  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - time_start);
  std::cout << "Time taken by program: " << duration.count() << " microseconds"
            << "\n";


  return 0;
}
