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

  auto [items, locations] = create_item_vectors(raw_vector);
  if (locations.empty()) { return 1; }

  auto keyed_items = items;
  auto keyed_locations = locations;

  // calculate part 1
  make_moves(items, locations);
  const int64_t coordinate_sum{ calculate_coordinate_sum(items) };

  // calculate part 2
  constexpr int64_t key = 811589153;
  constexpr int rounds = 10;
  
  apply_decryption_key(keyed_items, key);
  for (auto mix_round{0}; mix_round < rounds; ++mix_round) {
    make_moves(keyed_items, keyed_locations);
  }

  const int64_t keyed_sum{calculate_coordinate_sum(keyed_items)};


  std::cout << "Advent of Code " << AofCode_Cpp::cmake::campaign_year << " "
            << AofCode_Cpp::cmake::campaign_day << '\n';
  std::cout << "Part 1 solution: Coordinate sum = " << coordinate_sum << '\n';
  std::cout << "Part 2 solution: Keyed Coordinate sum = " << keyed_sum << '\n';

  return 0;
}
