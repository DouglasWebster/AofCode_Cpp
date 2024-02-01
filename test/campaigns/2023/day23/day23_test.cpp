#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include <iostream>

#include <2023_day23.hpp>

// start with a test case that does nothing but fail.

TEST_CASE(" 2023 day23 testing", "[day23]")
{
    std::string data_file = CURRENT_LIST_DIR;
  data_file += "/test.txt";

  const AoCLib::char_data puzzle_test_data{ AoCLib::vectorise_char_data(data_file) };

  SECTION ("check creation of trail map"){
    TrailMap trail_map{build_trails(puzzle_test_data)};

    CHECK(trail_map.size() == puzzle_test_data.size() * puzzle_test_data[0].size() );
  }
}
