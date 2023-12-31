#include <chrono>
#include <iostream>
#include <numeric>

#include "2023_day07.hpp"

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

  Hands hands(build_hands(puzzle_data));
  order_hands_by_strength(hands);
  rank_hands(hands);

  const int64_t total_winnings{ std::accumulate(hands.begin(), hands.end(), 0, [](int sum, const Hand &hand){
    return sum + hand.winnings;
  })};

  strengthen_hands(hands);
  rank_hands(hands);

  const int64_t new_winnings{ std::accumulate(hands.begin(), hands.end(), 0, [](int sum, const Hand &hand){
    return sum + hand.winnings;
  })};


  std::cout << "Advent of Code " << AofCode_Cpp::cmake::campaign_year << " "
            << AofCode_Cpp::cmake::campaign_day << '\n';
  std::cout << "Part 1 solution: Total winning  = " << total_winnings << '\n';
  std::cout << "Part 2 solution: New winnings = " << new_winnings << '\n';

  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - time_start);
  std::cout << "Time taken by program: " << duration.count() << " microseconds"
            << "\n";


  return 0;
}
