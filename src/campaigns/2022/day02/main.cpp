#include <algorithm>
#include <iostream>
#include <numeric>

#include "2022_day02.hpp"

int main()
{

  std::string data_file = CURRENT_LIST_DIR;
  data_file += "/input.txt";

  const AoCLib::str_data raw_vector{ AoCLib::vectorise_string_data(data_file) };

  // if (raw_vector.empty()) {
  //   std::cout << "No data to analyse!  Terminating program.";
  //   return 0;
  // }

  const strategy moves{ collate_moves(raw_vector) };

  const int first_solution = std::accumulate(
    moves.begin(), moves.end(), 0, [](int accumulator, const std::pair<std::string, std::string> &move) {
      return accumulator + first_strategy(move);
    });
  const int second_solution = std::accumulate(
    moves.begin(), moves.end(), 0, [](int accumulator, const std::pair<std::string, std::string> &move) {
      return accumulator + second_strategy(move);
    });

  std::cout << "Advent of Code " << AofCode_Cpp::cmake::campaign_year << " " << AofCode_Cpp::cmake::campaign_day
            << '\n';
  std::cout << "Part 1 solution: " << first_solution << '\n';
  std::cout << "Part 2 solution: " << second_solution << '\n';

  return 0;
}
