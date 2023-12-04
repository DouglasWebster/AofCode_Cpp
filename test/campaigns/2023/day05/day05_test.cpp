#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>

#include <2023_day05.hpp>

// start with a test case that does nothing but fail.

TEST_CASE(" 2023 day05 ", "[day05]")
{
    std::stringstream tmp_file;
  tmp_file << std::tmpnam(nullptr) << "_2023_day04.txt";// NOLINT: This is not thread safe!

  std::string test_data = "Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53\n";
  test_data += "Card 2: 13 32 20 16 61 | 61 30 68 82 17 32 24 19\n";
  test_data += "Card 3:  1 21 53 59 44 | 69 82 63 72 16 21 14  1\n";
  test_data += "Card 4: 41 92 73 84 69 | 59 84 76 51 58  5 54 83\n";
  test_data += "Card 5: 87 83 26 28 32 | 88 30 70 12 93 22 82 36\n";
  test_data += "Card 6: 31 18 13 56 72 | 74 77 10 23 35 67 36 11";


  std::ofstream test_file{ tmp_file.str() };
  if (!test_file) {
    std::cerr << "Test file " << tmp_file.str() << "could not be opened for writing\n";
  }

  test_file << test_data << std::flush;

  AoCLib::line_data puzzle_test_data{ AoCLib::vectorise_line_data(tmp_file.str()) };

  // clean up after each test
  std::filesystem::path temp_file_path = tmp_file.str();
  if (std::filesystem::exists(temp_file_path)) { std::filesystem::remove(temp_file_path); }
}
