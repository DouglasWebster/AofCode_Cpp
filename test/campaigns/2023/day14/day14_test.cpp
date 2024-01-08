#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

#include <2023_day14.hpp>

TEST_CASE(" 2023 day14 testing", "[day14]")
{
  std::stringstream tmp_file;
  tmp_file << std::tmpnam(nullptr) << "_2023_day14.txt"; // NOLINT: This is not thread safe!

  std::string test_data = "O....#....\n";
  test_data += "O.OO#....#\n";
  test_data += ".....##...\n";
  test_data += "OO.#O....O\n";
  test_data += ".O.....O#.\n";
  test_data += "O.#..O.#.#\n";
  test_data += "..O..#O..O\n";
  test_data += ".......O..\n";
  test_data += "#....###..\n";
  test_data += "#OO..#....";

  std::ofstream test_file{ tmp_file.str() };
  if (!test_file) {
    std::cerr << "Test file " << tmp_file.str() << "could not be opened for writing\n";
  }
  test_file << test_data << std::flush;

  AoCLib::char_data puzzle_test_data{ AoCLib::vectorise_char_data(tmp_file.str()) };

  SECTION("check creation of platform")
  {
    Platform platform{ create_platform(puzzle_test_data) };

    CHECK(platform.size() == 10);
    CHECK_THAT(platform[0],
      Catch::Matchers::Equals(Row{ 'O', '.', '.', '.', '.', '#', '.', '.', '.', '.' }));
    CHECK_THAT(platform[9],
      Catch::Matchers::Equals(Row{ '#', 'O', 'O', '.', '.', '#', '.', '.', '.', '.' }));
  }

  SECTION("check that tilt table tilts north by default and return the balls moved correctly")
  {
    Platform platform{ create_platform(puzzle_test_data) };
    Platform exptected{
      { 'O', 'O', 'O', 'O', '.', '#', '.', 'O', '.', '.' },
      { 'O', 'O', '.', '.', '#', '.', '.', '.', '.', '#' },
      { 'O', 'O', '.', '.', 'O', '#', '#', '.', '.', 'O' },
      { 'O', '.', '.', '#', '.', 'O', 'O', '.', '.', '.' },
      { '.', '.', '.', '.', '.', '.', '.', '.', '#', '.' },
      { '.', '.', '#', '.', '.', '.', '.', '#', '.', '#' },
      { '.', '.', 'O', '.', '.', '#', '.', 'O', '.', 'O' },
      { '.', '.', 'O', '.', '.', '.', '.', '.', '.', '.' },
      { '#', '.', '.', '.', '.', '#', '#', '#', '.', '.' },
      { '#', '.', '.', '.', '.', '#', '.', '.', '.', '.' },
    };

    Platform tilted_platform{ tilt_platform(platform) };

    CHECK_THAT(tilted_platform, Catch::Matchers::Equals(exptected));
    CHECK_THAT(tilted_platform[0], Catch::Matchers::Equals(exptected[0]));
    CHECK_THAT(tilted_platform[1], Catch::Matchers::Equals(exptected[1]));
    CHECK_THAT(tilted_platform[2], Catch::Matchers::Equals(exptected[2]));
    CHECK_THAT(tilted_platform[3], Catch::Matchers::Equals(exptected[3]));
    CHECK_THAT(tilted_platform[4], Catch::Matchers::Equals(exptected[4]));
    CHECK_THAT(tilted_platform[5], Catch::Matchers::Equals(exptected[5]));
    CHECK_THAT(tilted_platform[6], Catch::Matchers::Equals(exptected[6]));
    CHECK_THAT(tilted_platform[7], Catch::Matchers::Equals(exptected[7]));
    CHECK_THAT(tilted_platform[8], Catch::Matchers::Equals(exptected[8]));
    CHECK_THAT(tilted_platform[9], Catch::Matchers::Equals(exptected[9]));
    
  }

  SECTION("check the calculation of the total load") {
    Platform platform {create_platform(puzzle_test_data)};
    Platform tilted_platform{tilt_platform(platform)};

    CHECK(calculate_load(tilted_platform) == 136);

  }


  // clean up after each test
  std::filesystem::path temp_file_path = tmp_file.str();
  if (std::filesystem::exists(temp_file_path)) { std::filesystem::remove(temp_file_path); }
}
