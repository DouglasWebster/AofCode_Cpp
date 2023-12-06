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
  std::stringstream tmp_file;
  tmp_file << std::tmpnam(nullptr) << "_2023_day04.txt";// NOLINT: This is not thread safe!

  std::string test_data = "Time:      7  15   30\n";
  test_data += "Distance:  9  40  200";

  std::ofstream test_file{ tmp_file.str() };
  if (!test_file) {
    std::cerr << "Test file " << tmp_file.str() << "could not be opened for writing\n";
  }

  test_file << test_data << std::flush;

  AoCLib::line_data puzzle_test_data{ AoCLib::vectorise_line_data(tmp_file.str()) };

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

  // clean up after each test
  std::filesystem::path temp_file_path = tmp_file.str();
  if (std::filesystem::exists(temp_file_path)) { std::filesystem::remove(temp_file_path); }

  
}
