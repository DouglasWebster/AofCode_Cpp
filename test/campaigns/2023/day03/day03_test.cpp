#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

#include <2023_day03.hpp>

// start with a test case that does nothing but fail.

TEST_CASE(" 2023 day03 testing", "[day03]")
{
    std::stringstream tmp_file;
  tmp_file << std::tmpnam(nullptr) << "_2023_day03.txt";// NOLINT: This is not thread safe!

  std::string test_data = "467..114..\n";
  test_data += "...*......\n";
  test_data += "..35..633.\n";
  test_data += "......#...\n";
  test_data += "617*......\n";
  test_data += ".....+.58.\n";
  test_data += "..592.....\n";
  test_data += "......755.\n";
  test_data += "...$.*....\n";
  test_data += ".664.598..";



  std::ofstream test_file{ tmp_file.str() };
  if (!test_file) {
    std::cerr << "Test file " << tmp_file.str() << "could not be opened for writing\n";
  }
  test_file << test_data << std::flush;

  AoCLib::char_data puzzle_test_data{ AoCLib::vectorise_char_data(tmp_file.str()) };

  SECTION( "check creation of raw data") {
    std::vector<char> row_1_vector{'4','6','7','.','.','1','1','4','.','.'};
    CHECK_THAT(puzzle_test_data[0], Catch::Matchers::Equals(row_1_vector));
    std::vector<char>row_10_vector {'.','6','6','4','.','5','9','8','.','.'};
    CHECK_THAT(puzzle_test_data[9], Catch::Matchers::Equals(row_10_vector));
  }

  SECTION ("check creation of inflated schematic") {
    CHECK(inflate_schematic(Schematic{}).size() == 0);

    Schematic search_scematic{inflate_schematic(puzzle_test_data)};

    CHECK(search_scematic.size() == 12);
    CHECK(search_scematic[0].size() == 12);

    std::vector<char> blank_row(12, '.');

    CHECK_THAT(search_scematic[0], Catch::Matchers::Equals(blank_row));
    CHECK_THAT(search_scematic[11], Catch::Matchers::Equals(blank_row));

    std::vector<char> row_1_vector{'.','4','6','7','.','.','1','1','4','.','.','.'};
    CHECK_THAT(search_scematic[1], Catch::Matchers::Equals(row_1_vector));
    std::vector<char>row_10_vector {'.','.','6','6','4','.','5','9','8','.','.','.'};
    CHECK_THAT(search_scematic[10], Catch::Matchers::Equals(row_10_vector));

  }

  SECTION("check test data returns correct answer") {
    Schematic search_schematic{inflate_schematic(puzzle_test_data)};
    PossibleGears possible_gears{};

    CHECK(calculate_partno_sum(search_schematic, possible_gears) == 4361 );

    int64_t gear_ration_product{};
    for(const auto & gear : possible_gears ) {
        if(gear.second.first == 2) {
            gear_ration_product += gear.second.second;
        }
    }

    CHECK(gear_ration_product == 467835);
  }

  // clean up after each test
  std::filesystem::path temp_file_path = tmp_file.str();
  if (std::filesystem::exists(temp_file_path)) { std::filesystem::remove(temp_file_path); }

}
