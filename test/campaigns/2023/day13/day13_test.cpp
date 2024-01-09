#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

#include <2023_day13.hpp>

TEST_CASE(" 2023 day13 testing", "[day12]")
{
  std::string data_file = CURRENT_LIST_DIR;
  data_file += "/test.txt";

  AoCLib::str_data puzzle_test_data{ AoCLib::vectorise_string_data(data_file) };


  SECTION("check building patterns")
  {
    Patterns patterns{ get_patterns(puzzle_test_data) };

    CHECK(patterns.size() == 2);
    CHECK_THAT(patterns[0],
      Catch::Matchers::Equals(Pattern{ "#.##..##.",
        "..#.##.#.",
        "##......#",
        "##......#",
        "..#.##.#.",
        "..##..##.",
        "#.#.##.#." }));

    CHECK_THAT(patterns[1],
      Catch::Matchers::Equals(Pattern{ "#...##..#",
        "#....#..#",
        "..##..###",
        "#####.##.",
        "#####.##.",
        "..##..###",
        "#....#..#" }));
  }

  SECTION("check horizontal reflection ") {
    Patterns patterns(get_patterns(puzzle_test_data));

    CHECK(is_horizontal_reflection(patterns[0]) == 0);
    CHECK(is_horizontal_reflection(patterns[1]) == 4);
  }

  SECTION("check vertical reflection") {
    Patterns patterns(get_patterns(puzzle_test_data));
    
    CHECK(is_vertical_reflection(patterns[0]) == 5);
    CHECK(is_vertical_reflection(patterns[1]) == 0);

  }

}
