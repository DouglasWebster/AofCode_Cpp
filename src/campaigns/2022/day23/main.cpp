#include <chrono>
#include <iostream>

#include "2022_day23.hpp"

int main()
{

  auto time_start = std::chrono::high_resolution_clock::now();

  std::string data_file = CURRENT_LIST_DIR;
  data_file += "/input.txt";

  GroveMap grove_map{ AoCLib::vectorise_char_data(data_file) };

  if (grove_map.empty()) {
    std::cout << "No data to analyse!  Terminating program.";
    return 0;
  }

  int rounds{ 0 };
  bool some_movement{ true };
  Direction prefered_direction{ Direction::north };
  constexpr int part_1_rounds{ 10 };
  int spaces_after_10_rounds{ 0 };

  while (some_movement) {
    rounds++;
    grove_map = create_next_map(grove_map);
    const MovementMap allowable_locations{ mark_allowable_positions(
      grove_map, prefered_direction) };
    some_movement = do_movement(grove_map, allowable_locations);
    if (rounds == part_1_rounds) { spaces_after_10_rounds = count_empty_ground(grove_map); }

    switch (prefered_direction) {
    case Direction::north:
      prefered_direction = Direction::south;
      break;
    case Direction::south:
      prefered_direction = Direction::west;
      break;
    case Direction::west:
      prefered_direction = Direction::east;
      break;
    case Direction::east:
      prefered_direction = Direction::north;
      break;
    default:
      break;
    }
  }


  std::cout << "Advent of Code " << AofCode_Cpp::cmake::campaign_year << " "
            << AofCode_Cpp::cmake::campaign_day << '\n';
  std::cout << "Part 1 solution: after 10 moves there are " << spaces_after_10_rounds
            << " empty tiles.\n";
  std::cout << "Part 2 solution: The first round where there is no movement is round " << rounds << '\n';


  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - time_start);
  std::cout << "Time taken by program: " << duration.count() << " microseconds"
            << "\n";

  return 0;
}
