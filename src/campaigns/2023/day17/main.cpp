#include <chrono>
#include <iostream>

#include "2023_day17.hpp"

int main()
{
  std::string data_file = CURRENT_LIST_DIR;
  data_file += "/input.txt";

  const AoCLib::char_data puzzle_data{ AoCLib::vectorise_char_data(data_file) };

  auto time_start = std::chrono::high_resolution_clock::now();
 
  Edges edges{ create_edges(puzzle_data) };
  const size_t nodes{ puzzle_data.size() * puzzle_data[0].size() };

  City city(edges, nodes);

  auto [block, energy] = energy_used(city);
  auto [ultra_block, ultra_energy] = energy_used(city, 4, 10);

  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - time_start);
  std::cout << "Time taken by program: " << duration.count() << " microseconds"
            << "\n";

  std::cout << "Advent of Code " << AofCode_Cpp::cmake::campaign_year << " "
            << AofCode_Cpp::cmake::campaign_day << '\n';
  std::cout << "Part 1 solution: Min heat loss is " << energy << '\n';
  std::cout << "Part 2 solution: Min heat loss with Ultra crucibles is " << ultra_energy << '\n';

  return 0;
}
