#include <iostream>

#include "2022_day20.hpp"

int main()
{

  std::string data_file = CURRENT_LIST_DIR;
  data_file += "/input.txt";

  const AoCLib::int_data raw_vector{ AoCLib::vectorise_int_data(data_file) };

  if (raw_vector.empty()) {
    std::cout << "No data to analyse!  Terminating program.";
    return 0;
  }

  Items items{create_item_list(raw_vector)};

  make_moves(items);
  const int coordinate_sum{calculate_coordinate_sum(items)};

  std::cout << "Advent of Code " << AofCode_Cpp::cmake::campaign_year << " "
            << AofCode_Cpp::cmake::campaign_day << '\n';
  std::cout << "Part 1 solution: Coordinate sum = " << coordinate_sum << '\n';
  std::cout << "Part 2 solution:\n";

  return 0;
}
