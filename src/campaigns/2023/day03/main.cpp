#include <chrono>
#include <iostream>
#include <numeric>

#include "2023_day03.hpp"

int main()
{
  auto time_start = std::chrono::high_resolution_clock::now();

  std::string data_file = CURRENT_LIST_DIR;
  data_file += "/input.txt";

  const AoCLib::char_data engine_schematic{ AoCLib::vectorise_char_data(data_file) };

  if (engine_schematic.empty()) {
    std::cout << "No data to analyse!  Terminating program.";
    return 0;
  }

  PossibleGears possible_gears{};

  Schematic inflated_schematic{ inflate_schematic(engine_schematic) };
  const int part_no_sum{ calculate_partno_sum(inflated_schematic, possible_gears) };

  const int64_t gear_ration_product = std::accumulate(possible_gears.begin(), possible_gears.end(), 0, [](int64_t x, const auto &gear) {
    if (gear.second.first == 2) { return x + gear.second.second; }
    return x;
  });


  std::cout << "Advent of Code " << AofCode_Cpp::cmake::campaign_year << " "
            << AofCode_Cpp::cmake::campaign_day << '\n';
  std::cout << "Part 1 solution: the sum of the part numbers is " << part_no_sum << '\n';
  std::cout << "Part 2 solution: the product of the gear ratios is " << gear_ration_product << '\n';

  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - time_start);
  std::cout << "Time taken by program: " << duration.count() << " microseconds"
            << "\n";

  return 0;
}
