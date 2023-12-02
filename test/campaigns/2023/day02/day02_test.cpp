#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include <iostream>

#include <2023_day02.hpp>

// start with a test case that does nothing but fail.

TEST_CASE(" 2023 day02 ", "[day02]")
{
  AoCLib::line_data raw_data{ { "Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green" },
    { "Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue" },
    { "Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red" },
    { "Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red" },
    { "Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green" } };

  SECTION("check parsing of raw data into games")
  {
    Games games{ build_games(raw_data) };
    Reveals game1_reveals{};
    Reveal reveal1{CubeSet(Cube::blue, 3), CubeSet(Cube::red, 4 )};
    Reveal reveal2{CubeSet( Cube::red, 1), CubeSet(Cube::green, 2 ), CubeSet(Cube::blue, 6 )};
    Reveal reveal3{CubeSet(Cube::green, 2 )};
    game1_reveals.push_back(reveal1);
    game1_reveals.push_back(reveal2);
    game1_reveals.push_back(reveal3);
    Reveals game5_reveals{};
    Reveal reveal4{CubeSet(Cube::red, 6), CubeSet(Cube::blue, 1 ), CubeSet(Cube::green, 3)};
    Reveal reveal5{CubeSet(Cube::blue, 2), CubeSet(Cube::red, 1 ), CubeSet(Cube::green, 2)};
    game5_reveals.push_back(reveal4);
    game5_reveals.push_back(reveal5);
    CHECK(games[0].game_no == 1);
    CHECK_THAT(games[0].reveals[0], Catch::Matchers::Equals(reveal1));
    CHECK_THAT(games[0].reveals[1], Catch::Matchers::Equals(reveal2));
    CHECK_THAT(games[0].reveals[2], Catch::Matchers::Equals(reveal3));
    CHECK(games[4].game_no == 5);
    CHECK_THAT(games[4].reveals[0], Catch::Matchers::Equals(reveal4));
    CHECK_THAT(games[4].reveals[1], Catch::Matchers::Equals(reveal5));

  }

  SECTION(" check accumulaion of possible game IDs") {
    Games games{build_games(raw_data)};
    CHECK(count_possible_games(games) == 8);
  }

  SECTION(" check the power sum of the games") {
    Games games{build_games(raw_data)};
    CHECK(sum_set_powers(games) == 2286);
  }
}
