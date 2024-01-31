#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include <iostream>

#include <2023_day22.hpp>

// start with a test case that does nothing but fail.

TEST_CASE(" 2023 day22 testing ", "[day22]")
{
  std::string data_file = CURRENT_LIST_DIR;
  data_file += "/test.txt";

  const AoCLib::line_data puzzle_test_data{ AoCLib::vectorise_line_data(data_file) };

  SECTION("check the bricks are created correctly")
  {
    auto bricks{ get_bricks(puzzle_test_data) };

    CHECK(bricks.size() == puzzle_test_data.size());

    CHECK(bricks[0].grounded == true);
  }

  SECTION("check the bricks drop correctly")
  {
    auto bricks{ get_bricks(puzzle_test_data) };
    drop_bricks(bricks);

    CHECK(bricks.front().grounded == true);
    CHECK(bricks.back().grounded == true);
  }

  SECTION("check the count of bricks that can be disinteg")
  {
    auto bricks{ get_bricks(puzzle_test_data) };
    drop_bricks(bricks);

    CHECK(count_smashable(bricks) == 5);
  }

  SECTION("check counting chain reations")
  {
    auto bricks{ get_bricks(puzzle_test_data) };
    drop_bricks(bricks);

    Counted counted{};

    // a top brick shouldn't cascade anything
    CHECK(count_chain_reaction(bricks[6], bricks) == 0);

    // nothing mapped so should count them all
    CHECK(count_chain_reaction(bricks[0], bricks) == 6);

    size_t f_brick{ 5 };
    int f_brick_count{ count_chain_reaction(bricks[f_brick], bricks)}; //, counted) };
    counted.emplace(f_brick, f_brick_count);
    CHECK(f_brick_count == 1);
    CHECK(counted.size() == 1);

    size_t a_brick{ 0 };
    int a_brick_count{ count_chain_reaction(bricks[a_brick], bricks)}; //, counted) };
    counted.emplace(a_brick, a_brick_count);
    CHECK(a_brick_count == 6);
    CHECK(counted.size() == 2);
  }

  SECTION("check calculating total")
  {
    auto bricks{ get_bricks(puzzle_test_data) };
    drop_bricks(bricks);
    count_smashable(bricks);

    Counted counted{};
    int cascaded_sum{};

    for (size_t index{ bricks.size() }; index > 0; --index) {
      auto brick_id{ index - 1 };
      if (!bricks[brick_id].smashable) {
        auto cascaded{ count_chain_reaction(bricks[brick_id], bricks)}; //, counted) };
        cascaded_sum += cascaded;
        counted.emplace(brick_id, cascaded);
      }
    }

    CHECK(cascaded_sum == 7);
  }
}
