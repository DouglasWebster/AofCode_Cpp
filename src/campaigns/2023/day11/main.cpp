#include <chrono>
#include <iostream>
#include <numeric>

#include "2023_day11.hpp"

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

  Universe universe{ puzzle_data };
  const Galaxies original_galaxies(get_galaxies(universe));
  const GalaxyPairs pairs(pair_galaxies(original_galaxies));
  const int64_t original_separation{ calculate_galaxy_manhattan_seperation(pairs, original_galaxies) };

  expand_universe(universe);
  const Galaxies new_galaxies{ get_galaxies(universe) };
  const int64_t incresed_1_times_separaton{ calculate_galaxy_manhattan_seperation(
    pairs, new_galaxies) };

  constexpr int64_t million_inflation{ 1000000 };
  const int64_t separation_change{ incresed_1_times_separaton - original_separation };
  const int64_t million_times_inflation{ separation_change * million_inflation + original_separation
                                         - separation_change };


  std::cout << "Advent of Code " << AofCode_Cpp::cmake::campaign_year << " "
            << AofCode_Cpp::cmake::campaign_day << '\n';
  std::cout << "Part 1 solution: Total distance " << incresed_1_times_separaton << '\n';
  std::cout << "Part 2 solution: New total distance " << million_times_inflation << '\n';

  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - time_start);
  std::cout << "Time taken by program: " << duration.count() << " microseconds"
            << "\n";


  return 0;
}
