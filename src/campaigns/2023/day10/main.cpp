#include <chrono>
#include <iostream>
#include <numeric>

#include "2023_day10.hpp"

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

  LocationTypes locations{ set_locations(puzzle_data) };
  const MapData map_data{ build_map_data(puzzle_data, locations) };
  auto [start_positon, pipes] = map_data;

  const size_t steps{ count_steps(map_data) / 2 };

  auto direction{start_direction(puzzle_data, start_positon)};
  const AoCLib::char_data path_map{draw_map(start_positon, direction, puzzle_data)};

  const auto enclosed{count_enclosed(path_map)};

  std::cout << "Advent of Code " << AofCode_Cpp::cmake::campaign_year << " "
            << AofCode_Cpp::cmake::campaign_day << '\n';
  std::cout << "Part 1 solution: Farthest point is " << steps << " allong the loop\n";
  std::cout << "Part 2 solution: Enclosed tiles = " << enclosed << '\n';

  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - time_start);
  std::cout << "Time taken by program: " << duration.count() << " microseconds"
            << "\n";


  return 0;
}
