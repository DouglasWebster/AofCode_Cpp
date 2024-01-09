#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>

#include <2023_day06.hpp>

// start with a test case that does nothing but fail.

TEST_CASE(" 2023 day06 testing", "[day06]")
{
  std::string data_file = CURRENT_LIST_DIR;
  data_file += "/test.txt";

  AoCLib::line_data puzzle_test_data{ AoCLib::vectorise_line_data(data_file)};

  SECTION("check creation of Races vector") {
    Races races{{7, 9},{15, 40}, {30, 200}};
    CHECK_THAT(get_races(puzzle_test_data), Catch::Matchers::Equals(races));
  }

  SECTION("check calculation of max hold time") {
    Races races{get_races(puzzle_test_data)};
    CHECK(find_max_hold_time(races[0]) == 5);
    CHECK(find_max_hold_time(races[1]) == 11);
    CHECK(find_max_hold_time(races[2]) == 19);
  }

  SECTION("check calculation of number of winning ways") {
    CHECK(calc_number_of_winning_ways(Race{7,9}, 5) == 4);
    CHECK(calc_number_of_winning_ways(Race{15,40}, 11) == 8);
    CHECK(calc_number_of_winning_ways(Race{30,200}, 19) == 9);
  }
}
