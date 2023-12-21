#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include <iostream>

#include <2023_day18.hpp>

// start with a test case that does nothing but fail.

TEST_CASE(" 2023 day18 testing", "[day18]")
{
  std::string data_file = CURRENT_LIST_DIR;
  data_file += "/test.txt";

  const AoCLib::line_data puzzle_test_data{ AoCLib::vectorise_line_data(data_file) };

  DigPlan dig_plan{ create_plan(puzzle_test_data) };

  SECTION("check shoelace computation")
  {
    DigiPlanInfo info{ create_vertices(dig_plan) };

    auto area{ shoelace_area(info.second) };
    CHECK (info.first == 38);

    area += info.first / 2 + 1;

    CHECK(area == 62.0);
  }
}
