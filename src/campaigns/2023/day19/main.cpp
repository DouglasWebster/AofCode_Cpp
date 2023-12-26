#include <chrono>
#include <iostream>
#include <numeric>

#include "2023_day19.hpp"

int main()
{
  auto time_start = std::chrono::high_resolution_clock::now();

  std::string data_file = CURRENT_LIST_DIR;
  data_file += "/input.txt";

  const AoCLib::line_data puzzle_data{ AoCLib::vectorise_line_data(data_file) };

  if (puzzle_data.empty()) {
    std::cout << "No data to analyse!  Terminating program.";
    return 0;
  }

  auto parts{ create_parts_inventory(puzzle_data) };
  auto workflows(create_workflows(puzzle_data));
  auto start{ build_indexes(workflows) };

  for (auto &part : parts) { do_workflows(workflows, part, start); }

  const int ratings_total{ accepted_ratings_total(parts) };

  auto accepted_ratings{ get_accepted_ratings(workflows, start) };
  
  int64_t total{};

  for (const auto &result : accepted_ratings) {
    int64_t result_total{ 1 };
    result_total *= (result.x_left.second - result.x_left.first + 1);
    result_total *= (result.m_left.second - result.m_left.first + 1);
    result_total *= (result.a_left.second - result.a_left.first + 1);
    result_total *= (result.s_left.second - result.s_left.first + 1);
    total += result_total;
  }

  std::cout << "Advent of Code " << AofCode_Cpp::cmake::campaign_year << " "
            << AofCode_Cpp::cmake::campaign_day << '\n';
  std::cout << "Part 1 solution: Accepted parts total = " << ratings_total << '\n';
  std::cout << "Part 2 solution: Distinct combinations of accepted ratings " << total << '\n';


  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - time_start);
  std::cout << "Time taken by program: " << duration.count() << " microseconds"
            << "\n";

  return 0;
}
