#include <chrono>
#include <iostream>
#include <numeric>
#include <algorithm>

#include "2023_day09.hpp"

int main()
{
  auto time_start = std::chrono::high_resolution_clock::now();

  std::string data_file = CURRENT_LIST_DIR;
  data_file += "/input.txt";

  const AoCLib::int_data puzzle_data{ AoCLib::vectorise_int_data(data_file) };

  if (puzzle_data.empty()) {
    std::cout << "No data to analyse!  Terminating program.";
    return 0;
  }

  Tree forward_tree{};
  for (const auto &data : puzzle_data) {
    Sequence sequence{};
    sequence.resize(data.size());
    std::copy(data.begin(), data.end(), sequence.begin());
    History history{ build_history(sequence) };
    extrapolate_next_value(history);
    forward_tree.emplace_back(history);
  };
  
  Tree reverse_tree{};
  for (const auto &data : puzzle_data) {
    Sequence sequence{};
    for (auto r_iter = data.rbegin(); r_iter != data.rend();  ++r_iter) //NOLINT
    {
      sequence.emplace_back(*r_iter);
    }
    History history{ build_history(sequence) };
    extrapolate_next_value(history);
    reverse_tree.emplace_back(history);
  };

  const int64_t forward_sum{ calculate_extrapolated_sum(forward_tree) };
  const int64_t reverse_sum{ calculate_extrapolated_sum(reverse_tree) };

  std::cout << "Advent of Code " << AofCode_Cpp::cmake::campaign_year << " "
            << AofCode_Cpp::cmake::campaign_day << '\n';
  std::cout << "Part 1 solution: Extrapolate sum = " << forward_sum << '\n';
  std::cout << "Part 2 solution: Extrapolate reverse sum = " << reverse_sum << '\n';

  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - time_start);
  std::cout << "Time taken by program: " << duration.count() << " microseconds"
            << "\n";


  return 0;
}
