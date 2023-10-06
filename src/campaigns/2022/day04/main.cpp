#include <chrono>
#include <iostream>
#include <numeric>

#include "2022_day04.hpp"


int main()
{
  auto time_start = std::chrono::high_resolution_clock::now();

  std::string data_file = CURRENT_LIST_DIR;
  data_file += "/input.txt";

  const AoCLib::str_data raw_vector{ AoCLib::vectorise_string_data(data_file, ',') };

  if (raw_vector.empty()) {
    std::cout << "No data to analyse!  Terminating program.";
    return 0;
  }

  Assignments assignments{ collate_assignments(raw_vector) };

  const int fully_contained_ranges = std::accumulate(
    assignments.begin(), assignments.end(), 0, [](int accumulator, auto assignment) {
      return (contains_fully(assignment) ? ++accumulator : accumulator);
    });
  
  const int overlaps = std::accumulate(
    assignments.begin(), assignments.end(), 0, [](int accumulator, auto assignment) {
      return (overlapping(assignment) ? ++accumulator : accumulator);
    });
  std::cout << "Advent of Code " << AofCode_Cpp::cmake::campaign_year << " "
            << AofCode_Cpp::cmake::campaign_day << '\n';
  std::cout << "Part 1 solution: " << fully_contained_ranges << '\n';
  std::cout << "Part 2 solution:" << overlaps << '\n';

  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - time_start);
  std::cout << "Time taken by program: " << duration.count() << " microseconds"
            << "\n";
  return 0;
}
