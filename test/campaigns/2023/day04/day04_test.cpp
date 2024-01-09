#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>

#include <2023_day04.hpp>

// start with a test case that does nothing but fail.

TEST_CASE(" 2023 day04 testing ", "[day04]")
{
  std::string data_file = CURRENT_LIST_DIR;
  data_file += "/test1.txt";

  AoCLib::line_data puzzle_test_data{ AoCLib::vectorise_line_data(data_file) };

  SECTION("check data maps creation")
  {

    WinningsNumberMap expected_win_map{};
    CardNumberMap expected_card_map{};

    convert_raw_data_to_maps(puzzle_test_data, expected_win_map, expected_card_map);
    CardNumbers win_map_1{ expected_win_map[1] };
    CardNumbers exp_map_1{ 41, 48, 83, 86, 17 };

    CHECK_THAT(win_map_1, Catch::Matchers::Equals(exp_map_1));
    CHECK_THAT(CardNumbers{ expected_win_map[6] },
      Catch::Matchers::Equals(CardNumbers{ 31, 18, 13, 56, 72 }));
    CHECK_THAT(CardNumbers{ expected_card_map[4] },
      Catch::Matchers::Equals(CardNumbers{ 59, 84, 76, 51, 58, 5, 54, 83 }));
  }

  SECTION("check the card winnings calculation")
  {

    WinningsNumberMap expected_win_map{};
    CardNumberMap expected_card_map{};

    convert_raw_data_to_maps(puzzle_test_data, expected_win_map, expected_card_map);

    CHECK(calculate_card_winnings(expected_win_map[1], expected_card_map[1]).second == 8);
    CHECK(calculate_card_winnings(expected_win_map[2], expected_card_map[2]).second == 2);
    CHECK(calculate_card_winnings(expected_win_map[3], expected_card_map[3]).second == 2);
    CHECK(calculate_card_winnings(expected_win_map[4], expected_card_map[4]).second == 1);
    CHECK(calculate_card_winnings(expected_win_map[5], expected_card_map[5]).second == 0);
    CHECK(calculate_card_winnings(expected_win_map[6], expected_card_map[6]).second == 0);

    CHECK(calculate_card_winnings(expected_win_map[1], expected_card_map[1]).first == 4);
    CHECK(calculate_card_winnings(expected_win_map[2], expected_card_map[2]).first == 2);
    CHECK(calculate_card_winnings(expected_win_map[3], expected_card_map[3]).first == 2);
    CHECK(calculate_card_winnings(expected_win_map[4], expected_card_map[4]).first == 1);
    CHECK(calculate_card_winnings(expected_win_map[5], expected_card_map[5]).first == 0);
    CHECK(calculate_card_winnings(expected_win_map[6], expected_card_map[6]).first == 0);
  }

  SECTION("check calculation of total scratchcards")
  {

    WinningsNumberMap expected_win_map{};
    CardNumberMap expected_card_map{};

    convert_raw_data_to_maps(puzzle_test_data, expected_win_map, expected_card_map);

    std::vector<int> card_copies(puzzle_test_data.size(), 1);

    inflate_card_copies(1, card_copies, 4);
    CHECK_THAT(card_copies, Catch::Matchers::Equals(std::vector<int>{ 1, 2, 2, 2, 2, 1 }));
    inflate_card_copies(2, card_copies, 2);
    CHECK_THAT(card_copies, Catch::Matchers::Equals(std::vector<int>{ 1, 2, 4, 4, 2, 1 }));
    inflate_card_copies(3, card_copies, 2);
    CHECK_THAT(card_copies, Catch::Matchers::Equals(std::vector<int>{ 1, 2, 4, 8, 6, 1 }));
    inflate_card_copies(4, card_copies, 1);
    CHECK_THAT(card_copies, Catch::Matchers::Equals(std::vector<int>{ 1, 2, 4, 8, 14, 1 }));
    inflate_card_copies(5, card_copies, 0);
    CHECK_THAT(card_copies, Catch::Matchers::Equals(std::vector<int>{ 1, 2, 4, 8, 14, 1 }));
    inflate_card_copies(6, card_copies, 0);
    CHECK_THAT(card_copies, Catch::Matchers::Equals(std::vector<int>{ 1, 2, 4, 8, 14, 1 }));

    CHECK(std::accumulate(card_copies.begin(), card_copies.end(), 0) == 30);
  }
}
