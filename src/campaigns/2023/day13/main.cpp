#include <chrono>
#include <iostream>
#include <numeric>

#include "2023_day13.hpp"

int main()
{
  auto time_start = std::chrono::high_resolution_clock::now();

  std::string data_file = CURRENT_LIST_DIR;
  data_file += "/input.txt";

  const AoCLib::str_data puzzle_data{ AoCLib::vectorise_string_data(data_file) };

  if (puzzle_data.empty()) {
    std::cout << "No data to analyse!  Terminating program.";
    return 0;
  }

  constexpr size_t multiplier{ 100 };

  const Patterns patterns{ get_patterns(puzzle_data) };

  size_t column_total{};
  size_t row_total{};

  for (const auto &pattern : patterns) {
    row_total += is_horizontal_reflection(pattern);
    column_total += is_vertical_reflection(pattern);
  }

  size_t repaired_total {};

  for (const auto &pattern : patterns) {
    const auto [horizontal, vertical] = do_all_repair(pattern);
    repaired_total += horizontal * multiplier + vertical;
  }

  std::cout << "Advent of Code " << AofCode_Cpp::cmake::campaign_year << " "
            << AofCode_Cpp::cmake::campaign_day << '\n';
  std::cout << "Part 1 solution: Unrepaired sum: " << row_total * multiplier + column_total << '\n';
  std::cout << "Part 2 solution:   Repaired sum: " << repaired_total << '\n';

  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - time_start);
  std::cout << "Time taken by program: " << duration.count() << " microseconds"
            << "\n";


  return 0;
}
