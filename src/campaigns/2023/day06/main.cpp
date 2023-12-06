#include <chrono>
#include <iostream>
#include <numeric>

#include "2023_day06.hpp"

int main()
{

  auto time_start = std::chrono::high_resolution_clock::now();

  std::string data_file = CURRENT_LIST_DIR;
  data_file += "/input.txt";

  const AoCLib::line_data raw_data{ AoCLib::vectorise_line_data(data_file) };

  if (raw_data.empty()) {
    std::cout << "No data to analyse!  Terminating program.";
    return 0;
  }

  const Races races{ get_races(raw_data) };

  int64_t margin_of_error{1};
  for (const auto &race : races) {
    const int64_t max_hold_time(find_max_hold_time(race));
    margin_of_error *= calc_number_of_winning_ways(race, max_hold_time);
  }

  const Race longer_race{55826490, 246144110121111};
  const int64_t max_hold_time{find_max_hold_time(longer_race)};
  const int64_t longer_margin = calc_number_of_winning_ways(longer_race, max_hold_time);

  std::cout << "Advent of Code " << AofCode_Cpp::cmake::campaign_year << " "
            << AofCode_Cpp::cmake::campaign_day << '\n';
  std::cout << "Part 1 solution: Margin of error is " << margin_of_error << '\n';
  std::cout << "Part 2 solution: Margin of error is " << longer_margin << '\n';

  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - time_start);
  std::cout << "Time taken by program: " << duration.count() << " microseconds"
            << "\n";

  return 0;
}
