#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

#include <2023_day12.hpp>

TEST_CASE(" 2023 day12 testing", "[day12]")
{
  std::stringstream tmp_file;
  tmp_file << std::tmpnam(nullptr) << "_2023_day12.txt";// NOLINT: This is not thread safe!

  std::string test_data = "???.### 1,1,3\n";
  test_data += ".??..??...?##. 1,1,3\n";
  test_data += "?#?#?#?#?#?#?#? 1,3,1,6\n";
  test_data += "????.#...#... 4,1,1\n";
  test_data += "????.######..#####. 1,6,5\n";
  test_data += "?###???????? 3,2,1";

  std::ofstream test_file{ tmp_file.str() };
  if (!test_file) {
    std::cerr << "Test file " << tmp_file.str() << "could not be opened for writing\n";
  }
  test_file << test_data << std::flush;


  AoCLib::char_data puzzle_test_data{ AoCLib::vectorise_char_data(tmp_file.str()) };
  // clean up after each test
  std::filesystem::path temp_file_path = tmp_file.str();
  if (std::filesystem::exists(temp_file_path)) { std::filesystem::remove(temp_file_path); }

  SECTION("check removal of tail of Springs") {
    const Springs springs{"?#?#?#?#?#?#?#?"};
    const DamagedGroups groups{1, 3, 1, 6};

    CHECK(first_item_fits(springs,groups) == 1);
  }
}