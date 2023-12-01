#include <chrono>
#include <iostream>

#include "2023_day01.hpp"

int main()
{

  auto time_start = std::chrono::high_resolution_clock::now();

  std::string data_file = CURRENT_LIST_DIR;
  data_file += "/input.txt";

  const AoCLib::str_data raw_vector{ AoCLib::vectorise_string_data(data_file) };

  if (raw_vector.empty()) {
    std::cout << "No data to analyse!  Terminating program.";
    return 0;
  }

    constexpr int decade_multiplier{10};
  int part_1_total{};
  int part_2_total{};
  for (const auto &data : raw_vector) { 
    part_1_total += first_digit(data[0]) * decade_multiplier + last_digit(data[0]);
    part_2_total += first_number(data[0]) * decade_multiplier + last_number(data[0]);
    }

  std::cout << "Advent of Code " << AofCode_Cpp::cmake::campaign_year << " "
            << AofCode_Cpp::cmake::campaign_day << '\n';
  std::cout << "Part 1 solution: calibration value sum = " << part_1_total << '\n';
  std::cout << "Part 2 solution: calibration value sum = " << part_2_total << '\n';

  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - time_start);
  std::cout << "Time taken by program: " << duration.count() << " microseconds"
            << "\n";
  return 0;
}
