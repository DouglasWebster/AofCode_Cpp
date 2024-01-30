#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include <iostream>

#include <2023_day22.hpp>

// start with a test case that does nothing but fail.

TEST_CASE(" 2023 day22 testing ", "[day22]")
{std::string data_file = CURRENT_LIST_DIR;
  data_file += "/test.txt";

  const AoCLib::line_data puzzle_test_data{ AoCLib::vectorise_line_data(data_file) };

  SECTION("check the bricks are created correctly") {
    auto bricks{get_bricks(puzzle_test_data)};

    CHECK(bricks.size() == puzzle_test_data.size());

    CHECK(bricks[0].grounded == true);
  }

  SECTION("check the bricks drop correctly") {
    auto bricks{get_bricks(puzzle_test_data)};
    drop_bricks(bricks);

    CHECK(bricks.front().grounded == true);
    CHECK(bricks.back().grounded == true);
  }

  SECTION ("check the count of bricks that can be disinteg") {

    auto bricks{get_bricks(puzzle_test_data)};
    drop_bricks(bricks);

    CHECK(count_smashable(bricks) == 5);
  }

  SECTION("check sorting out levels indexes") {
    auto bricks{get_bricks(puzzle_test_data)};
    drop_bricks(bricks);
    auto sorted_indexes{index_brick_levels(bricks)};

    CHECK(std::get<0>(sorted_indexes[0]) == 6);
    CHECK(std::get<1>(sorted_indexes[0]) == 5);
    CHECK(std::get<0>(sorted_indexes[6]) == 0);
    CHECK(std::get<1>(sorted_indexes[6]) == 1);
    CHECK(std::get<1>(sorted_indexes[5]) == 2);
    CHECK(std::get<1>(sorted_indexes[2]) == 3);
  }
}
