#include <algorithm>
#include <chrono>
#include <iostream>
#include <numeric>

#include "2022_day03.hpp"

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

  Contents contents{ collate_contents(raw_vector) };

  Rucksacks rucksacks{};
  rucksacks.resize(contents.size());

  std::transform(
    contents.begin(), contents.end(), rucksacks.begin(), [](auto items) { return get_compartments(items); });

  std::vector<char> common_items;
  common_items.resize(rucksacks.size());

  std::transform(rucksacks.begin(), rucksacks.end(), common_items.begin(), [](const Rucksack &rucksack) {
    return find_common_item(rucksack);
  });

  const int priorities = std::accumulate(common_items.begin(), common_items.end(), 0, [](int accumulator, char item) {
    return accumulator + calculate_priority(item);
  });

  const int badges_sum{ calculate_badges(contents) };

  std::cout << "Advent of Code " << AofCode_Cpp::cmake::campaign_year << " " << AofCode_Cpp::cmake::campaign_day
            << '\n';
  std::cout << "Part 1 solution, priorities = " << priorities << '\n';
  std::cout << "Part 2 solution, badges sum = " << badges_sum << '\n';
  
  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - time_start);
  std::cout << "Time taken by program: " << duration.count() << " microseconds"
            << "\n";
  return 0;
}
