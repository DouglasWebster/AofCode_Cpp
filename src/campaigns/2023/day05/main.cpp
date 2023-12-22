#include <chrono>
#include <iostream>
#include <limits>

#include "2023_day05.hpp"


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

  const Seeds seeds{ build_seeds_vector(raw_data[0]) };

  const Catagories catagories{ build_catagories(raw_data) };

  auto min_location{ std::numeric_limits<size_t>::max() };

  for (auto seed : seeds) {
    const size_t check_location{ trace_seed(seed, catagories) };
    if (check_location < min_location) { min_location = check_location; }
  }

  RangeMap range_map{};
  build_map(range_map, raw_data, 3);

  SourceRanges source_ranges{ build_seed_ranges(raw_data[0]) };

  for (const auto &catagory : catagories) { adjust_mapping(source_ranges, catagory); }

  std::cout << "Advent of Code " << AofCode_Cpp::cmake::campaign_year << " "
            << AofCode_Cpp::cmake::campaign_day << '\n';
  std::cout << "Part 1 solution: Nearest seed location is " << min_location << '\n';
  std::cout << "Part 2 solution: Lowest location is " << source_ranges.front().first << '\n';

  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - time_start);
  std::cout << "Time taken by program: " << duration.count() << " microseconds"
            << "\n";


  return 0;
}
