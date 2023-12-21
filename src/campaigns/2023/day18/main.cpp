#include <chrono>
#include <iostream>
#include <numeric>

#include "2023_day18.hpp"

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

  const DigPlan dig_plan{ create_plan(puzzle_data) };

  const DigiPlanInfo info{ create_vertices(dig_plan) };

  auto total_area = shoelace_area(info.second) + info.first / 2 + 1;

  const DigPlan hex_dig_plan{ decode_hex(puzzle_data) };
  const DigiPlanInfo new_info{ create_vertices(hex_dig_plan) };

  auto new_total_area = shoelace_area(new_info.second) + new_info.first / 2 + 1;


  std::cout << "Advent of Code " << AofCode_Cpp::cmake::campaign_year << " "
            << AofCode_Cpp::cmake::campaign_day << '\n';
  std::cout << "Part 1 solution: Lagoon size is " << total_area << " cubic meters\n";
  std::cout << "Part 2 solution: New lagoon size is " << std::fixed << new_total_area << " cubic meters\n";

  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - time_start);
  std::cout << "Time taken by program: " << duration.count() << " microseconds"
            << "\n";


  return 0;
}
