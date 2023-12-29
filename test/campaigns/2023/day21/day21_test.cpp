#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include <iostream>

#include <2023_day21.hpp>

// start with a test case that does nothing but fail.

TEST_CASE(" 2023 day21 testing", "[day21]")
{
   std::string data_file = CURRENT_LIST_DIR;
  data_file += "/test.txt";

  const AoCLib::char_data puzzle_data{ AoCLib::vectorise_char_data(data_file) };

  CHECK(true);
}
