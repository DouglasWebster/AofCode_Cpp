#include <chrono>
#include <iostream>

#include "2023_day02.hpp"

int main()
{
  auto time_start = std::chrono::high_resolution_clock::now();

  std::string data_file = CURRENT_LIST_DIR;
  data_file += "/input.txt";

  const AoCLib::line_data raw_vector{ AoCLib::vectorise_line_data(data_file) };

  if (raw_vector.empty()) {
    std::cout << "No data to analyse!  Terminating program.";
    return 0;
  }

  

  const Games games{ build_games(raw_vector) };

  const int possible_sum{count_possible_games(games)};
  const int power_sum(sum_set_powers(games));

  std::cout << "Advent of Code " << AofCode_Cpp::cmake::campaign_year << " "
            << AofCode_Cpp::cmake::campaign_day << '\n';
  std::cout << "Part 1 solution: possible games ID sums = " << possible_sum << '\n';
  std::cout << "Part 2 solution: games power sum = " << power_sum << '\n';

  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - time_start);
  std::cout << "Time taken by program: " << duration.count() << " microseconds"
            << "\n";
  return 0;
}
