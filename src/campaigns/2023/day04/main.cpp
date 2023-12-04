#include <chrono>
#include <iostream>
#include <numeric>


#include "2023_day04.hpp"

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

  WinningsNumberMap winning_number_map{};
  CardNumberMap check_number_map{};

  convert_raw_data_to_maps(raw_data, winning_number_map, check_number_map);

  const int no_of_scratchards{ static_cast<int>(raw_data.size())};
  int pile_worth{};

  std::vector<int> card_copies(raw_data.size(), 1);

  for(int card_no{1}; card_no <= no_of_scratchards; ++card_no) {
    auto[copies, card_points] = calculate_card_winnings(winning_number_map[card_no], check_number_map[card_no]);
    if(copies == 0) {continue;};
    pile_worth += card_points;
    inflate_card_copies(card_no, card_copies, copies);
  }

  const int total_scratchcards { std::accumulate(card_copies.begin(), card_copies.end(), 0)};


  std::cout << "Advent of Code " << AofCode_Cpp::cmake::campaign_year << " "
            << AofCode_Cpp::cmake::campaign_day << '\n';
  std::cout << "Part 1 solution:  Scratchcard pile is worth " << pile_worth << " points\n";
  std::cout << "Part 2 solution: Total number of scratchcard is " << total_scratchcards <<'\n';

  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - time_start);
  std::cout << "Time taken by program: " << duration.count() << " microseconds"
            << "\n";

  return 0;
}
