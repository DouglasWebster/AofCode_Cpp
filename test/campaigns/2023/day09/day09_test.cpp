#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

#include <2023_day09.hpp>

Sequence convert_data_to_sequence(std::vector<int> &data)
{
  Sequence sequence{};
  for (auto item : data) { sequence.emplace_back(item); }
  return sequence;
}

TEST_CASE(" 2023 day09 testing", "[day09]")
{
  std::stringstream tmp_file;
  tmp_file << std::tmpnam(nullptr) << "_2023_day09.txt";// NOLINT: This is not thread safe!

  std::string test_data = "0 3 6 9 12 15\n";
  test_data += "1 3 6 10 15 21\n";
  test_data += "10 13 16 21 30 45\n";
  test_data += "9, 6, 3, 0, -3, -6, -9, -12";

  std::ofstream test_file{ tmp_file.str() };
  if (!test_file) {
    std::cerr << "Test file " << tmp_file.str() << "could not be opened for writing\n";
  }

  test_file << test_data << std::flush;

  AoCLib::int_data puzzle_test_data{ AoCLib::vectorise_int_data(tmp_file.str()) };

  SECTION("check building the history")
  {
    History tree_1_expected{ { 0, 3, 6, 9, 12, 15 }, { 3, 3, 3, 3, 3 }, { 0, 0, 0, 0 } };
    History tree_3_expected{
      { 10, 13, 16, 21, 30, 45 }, { 3, 3, 5, 9, 15 }, { 0, 2, 4, 6 }, { 2, 2, 2 }, { 0, 0 }
    };
    Sequence hist_4_line_1{ 9, 6, 3, 0, -3, -6, -9, -12};


    CHECK_THAT(build_history(convert_data_to_sequence(puzzle_test_data[0])),
      Catch::Matchers::Equals(tree_1_expected));
    CHECK_THAT(build_history(convert_data_to_sequence(puzzle_test_data[2])),
      Catch::Matchers::Equals(tree_3_expected));
    CHECK_THAT(build_history(
      convert_data_to_sequence(puzzle_test_data[3]))[0], Catch::Matchers::Equals(hist_4_line_1));
  }

  SECTION("check the creation of the last sequence item")
  {

    History tree_4_expected{ { 0, 3, 6, 9, 12, 15, 18 }, { 3, 3, 3, 3, 3, 3 }, { 0, 0, 0, 0, 0 } };
    History tree_6_expected{ { 10, 13, 16, 21, 30, 45, 68 },
      { 3, 3, 5, 9, 15, 23 },
      { 0, 2, 4, 6, 8 },
      { 2, 2, 2, 2 },
      { 0, 0, 0 } };

    History tree_4{ build_history(convert_data_to_sequence(puzzle_test_data[0])) };
    History tree_6{ build_history(convert_data_to_sequence(puzzle_test_data[2])) };
    History tree_7{ build_history(convert_data_to_sequence(puzzle_test_data[3])) };

    extrapolate_next_value(tree_4);
    extrapolate_next_value(tree_6);
    extrapolate_next_value(tree_7);

    CHECK_THAT(tree_4, Catch::Matchers::Equals(tree_4_expected));
    CHECK_THAT(tree_6, Catch::Matchers::Equals(tree_6_expected));
    CHECK_THAT(tree_7.front(), Catch::Matchers::Equals(Sequence{ 9, 6, 3, 0, -3, -6, -9, -12, -15}));
  }

  SECTION("check the calculation of the extrapolated values sum")
  {
    Tree tree{};
    for (auto &data : puzzle_test_data) {
      Sequence sequence{ convert_data_to_sequence(data) };
      History history{ build_history(sequence) };
      extrapolate_next_value(history);
      tree.emplace_back(history);
    };

    CHECK(calculate_extrapolated_sum(tree) == 99);
  }

  // clean up after each test
  std::filesystem::path temp_file_path = tmp_file.str();
  if (std::filesystem::exists(temp_file_path)) { std::filesystem::remove(temp_file_path); }
}
