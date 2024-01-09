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
  std::string data_file = CURRENT_LIST_DIR;
  data_file += "/test.txt";

  AoCLib::line_data puzzle_test_data{ AoCLib::vectorise_line_data(data_file)};

  SECTION("check the creation of the hands")
  {
    Hands hands{ build_hands(puzzle_test_data) };

    CHECK(hands.size() == 5);
    CHECK_THAT(hands[0].cards, Catch::Matchers::Equals(Cards{ 3, 2, 10, 3, 13 }));
    CHECK(hands[0].bid == 765);
  }

  SECTION("check hand strenght sort")
  {
    Hands hands(build_hands(puzzle_test_data));
    order_hands_by_strength(hands);

    CHECK(hands[0].strength == HandStrength::Three);
    CHECK(hands[1].strength == HandStrength::Three);
    CHECK(hands[2].strength == HandStrength::Two);
    CHECK(hands[3].strength == HandStrength::Two);
    CHECK(hands[4].strength == HandStrength::One);
  }

  SECTION("check hand ranking")
  {
    Hands hands(build_hands(puzzle_test_data));
    order_hands_by_strength(hands);
    rank_hands(hands);

    CHECK(hands.front().rank == static_cast<int>(hands.size()));
    CHECK(hands.back().rank == 1);
  }

  SECTION("check calcultion of winnings")
  {

    Hands hands(build_hands(puzzle_test_data));
    order_hands_by_strength(hands);
    rank_hands(hands);

    const int64_t total_winnings{ std::accumulate(
      hands.begin(), hands.end(), 0, [](int sum, const Hand &hand) {
        return sum + hand.winnings;
      }) };

    CHECK(total_winnings == 6440);
  }

  SECTION("check total with jokers") {

    Hands hands(build_hands(puzzle_test_data));
    strengthen_hands(hands);
    rank_hands(hands);

    const int64_t total_winnings{ std::accumulate(
      hands.begin(), hands.end(), 0, [](int sum, const Hand &hand) {
        return sum + hand.winnings;
      }) };

    CHECK(total_winnings == 5905);
    
  }
}
