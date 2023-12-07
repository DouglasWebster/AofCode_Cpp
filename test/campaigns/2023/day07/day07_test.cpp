#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>

#include <2023_day07.hpp>

// start with a test case that does nothing but fail.

TEST_CASE(" 2023 day07 testing", "[day07]")
{
  std::stringstream tmp_file;
  tmp_file << std::tmpnam(nullptr) << "_2023_day04.txt";// NOLINT: This is not thread safe!

  std::string test_data = "";
  test_data += "\n";
  ;

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
