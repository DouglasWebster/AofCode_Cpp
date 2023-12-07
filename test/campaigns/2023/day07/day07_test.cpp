#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>

#include <2023_day07.hpp>

TEST_CASE(" 2023 day07 testing", "[day07]")
{
  std::stringstream tmp_file;
  tmp_file << std::tmpnam(nullptr) << "_2023_day04.txt";// NOLINT: This is not thread safe!

  std::string test_data = "32T3K 765\n";
  test_data += "T55J5 684\n";
  test_data += "KK677 28\n";
  test_data += "KTJJT 220\n";
  test_data += "QQQJA 483\n";


  std::ofstream test_file{ tmp_file.str() };
  if (!test_file) {
    std::cerr << "Test file " << tmp_file.str() << "could not be opened for writing\n";
  }

  test_file << test_data << std::flush;

  AoCLib::line_data puzzle_test_data{ AoCLib::vectorise_line_data(tmp_file.str()) };

  SECTION( "check the creation of the hands") {
    Hands hands{build_hands(puzzle_test_data)};

    CHECK(hands.size() == 5);
    CHECK_THAT(hands[0].cards, Catch::Matchers::Equals(Cards{13,10,3,3,2}));
    CHECK(hands[0].bid == 765);
  }

  SECTION("check hand strenght sort") {
    Hands hands(build_hands(puzzle_test_data));
    order_hands_by_bid(hands);

    CHECK(hands[0].strength == HandStrength::Three);
    CHECK(hands[1].strength == HandStrength::Three);
    CHECK(hands[2].strength == HandStrength::Two);
    CHECK(hands[3].strength == HandStrength::Two);
    CHECK(hands[4].strength == HandStrength::One);
  }

  // SECTION("check hand ranking") {
  //   Hands hands(build_hands(puzzle_test_data));
  //   order_hands_by_bid(hands);
  //   rank_hands(hands);

  //   CHECK(hands.front().rank == static_cast<int>( hands.size()));
  //   CHECK(hands.back().rank == 1);
  // }

  SECTION("check calcultion of winnings") {

    Hands hands(build_hands(puzzle_test_data));
    order_hands_by_bid(hands);
    // rank_hands(hands);

    CHECK(calculate_winnings(hands) == 6440);
  }

  // clean up after each test
  std::filesystem::path temp_file_path = tmp_file.str();
  if (std::filesystem::exists(temp_file_path)) { std::filesystem::remove(temp_file_path); }
}
