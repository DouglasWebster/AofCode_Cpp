#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include <iostream>

#include <2023_day21.hpp>

// start with a test case that does nothing but fail.

TEST_CASE(" 2023 day21 testing", "[day21]")
{
  std::string data_file = CURRENT_LIST_DIR;
  data_file += "/test1.txt";

  const AoCLib::char_data puzzle_data{ AoCLib::vectorise_char_data(data_file) };

  SECTION("check garden creation")
  {
    Garden garden{ create_garden(puzzle_data) };

    CHECK(garden.size() == 121);

    CHECK(garden[60].type == 'S');
    CHECK(garden[0].north == max_location);
    CHECK(garden[120].east == max_location);
    CHECK(garden[119].east == garden.size() - 1);
    CHECK(garden[119].north == max_location);
  }

  SECTION("check making a move")
  {
    Garden garden{ create_garden(puzzle_data) };

    size_t start_pos{};
    for (; start_pos < garden.size(); ++start_pos) {
      if (garden[start_pos].type == 'S') { break; }
    }

    Possibles possibles{ start_pos };

    make_move(possibles, garden);

    CHECK(possibles.size() == 2);
    CHECK(possibles.find(49) != possibles.end());
    CHECK(possibles.find(start_pos - 1) != possibles.end());
  }

  SECTION("check after 6 steps")
  {
    Garden garden{ create_garden(puzzle_data) };

    size_t start_pos{};
    for (; start_pos < garden.size(); ++start_pos) {
      if (garden[start_pos].type == 'S') { break; }
    }

    Possibles possibles{ start_pos };

    for (int move{}; move < 6; ++move) { make_move(possibles, garden); }

    CHECK(possibles.size() == 16);
  }
}
