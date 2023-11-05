#include <iostream>

#include "2022_day21.hpp"

int main()
{

  std::string data_file = CURRENT_LIST_DIR;
  data_file += "/input.txt";

  const AoCLib::str_data raw_vector{ AoCLib::vectorise_string_data(data_file) };

  MonkeyData monkey_data{ create_data_vector(raw_vector) };

  build_tree_links(monkey_data);
  const int64_t part_1_solution{ calculate_totals(monkey_data, get_root_index(monkey_data)) };

  std::cout << "Advent of Code " << AofCode_Cpp::cmake::campaign_year << " "
            << AofCode_Cpp::cmake::campaign_day << '\n';
  std::cout << "Part 1 solution: " << part_1_solution << '\n';
  std::cout << "Part 2 solution:\n";

  return 0;
}
