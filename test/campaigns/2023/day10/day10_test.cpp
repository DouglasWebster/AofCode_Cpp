#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

#include <2023_day10.hpp>

TEST_CASE(" 2023 day10 testing", "[day10]")
{
  std::string data_file = CURRENT_LIST_DIR;
  data_file += "/test1.txt";

  AoCLib::char_data puzzle_test_data{ AoCLib::vectorise_char_data(data_file) };

  SECTION("check creation of map")
  {
    LocationTypes locations{ set_locations(puzzle_test_data) };

    MapData map_data{ build_map_data(puzzle_test_data, locations) };
    auto [start_positon, pipes] = map_data;

    CHECK(pipes[0].size() == 5);
    CHECK(pipes.size() == 5);
    CHECK(start_positon == Location{ 2, 0 });
    CHECK(pipes[2][0] == Pipe{ Connection::South, Connection::East });
  }

  SECTION("check counting steps")
  {
    LocationTypes locations{ set_locations(puzzle_test_data) };

    MapData map_data{ build_map_data(puzzle_test_data, locations) };
    auto [start_positon, pipes] = map_data;

    CHECK(count_steps(map_data) == 16);
  }

  SECTION("check draw map")
  {

    std::string test2_file = CURRENT_LIST_DIR;
    test2_file += "/test2.txt";

    const AoCLib::char_data puzzle_data{ AoCLib::vectorise_char_data(test2_file) };

    Location start{ find_start(puzzle_data) };
    auto direction{ start_direction(puzzle_data, start) };

    AoCLib::char_data path_map{ draw_map(start, direction, puzzle_data) };

    print_map(puzzle_data, "data.txt");
    print_map(path_map, "paths.txt");

    CHECK(count_enclosed(path_map) == 8);
  }
}