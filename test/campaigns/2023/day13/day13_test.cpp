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
  std::stringstream tmp_file;
  tmp_file << std::tmpnam(nullptr) << "_2023_day13.txt";// NOLINT: This is not thread safe!

  std::string test_data = "#.##..##.\n";
  test_data += "..#.##.#.\n";
  test_data += "##......#\n";
  test_data += "##......#\n";
  test_data += "..#.##.#.\n";
  test_data += "..##..##.\n";
  test_data += "#.#.##.#.\n";
  test_data += "\n";
  test_data += "#...##..#\n";
  test_data += "#....#..#\n";
  test_data += "..##..###\n";
  test_data += "#####.##.\n";
  test_data += "#####.##.\n";
  test_data += "..##..###\n";
  test_data += "#....#..#";

  std::ofstream test_file{ tmp_file.str() };
  if (!test_file) {
    std::cerr << "Test file " << tmp_file.str() << "could not be opened for writing\n";
  }
  test_file << test_data << std::flush;
  AoCLib::str_data puzzle_test_data{ AoCLib::vectorise_string_data(tmp_file.str()) };

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

  SECTION("check horizontal reflection with repair ") {
    Patterns patterns(get_patterns(puzzle_test_data));

    CHECK(is_horizontal_reflection(patterns[0], true) == 3);
    CHECK(is_horizontal_reflection(patterns[1], true) == 1);
  }

  SECTION("check vertical reflection with repair") {
    Patterns patterns(get_patterns(puzzle_test_data));
    
    CHECK(is_vertical_reflection(patterns[0], true) == 0);
    CHECK(is_vertical_reflection(patterns[1], true) == 0);

  }


  // clean up after each test
  std::filesystem::path temp_file_path = tmp_file.str();
  if (std::filesystem::exists(temp_file_path)) { std::filesystem::remove(temp_file_path); }
}
