#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

#include <2023_day16.hpp>

TEST_CASE(" 2023 day16 testing", "[day16]")
{
  std::string data_file = CURRENT_LIST_DIR;
  data_file += "/test.txt";

  const AoCLib::char_data puzzle_test_data{ AoCLib::vectorise_char_data(data_file) };

  SECTION("check construction of the contraption")
  {
    Contraption contraption{ build_contraption(puzzle_test_data) };

    Tile tile_1{contraption[12]}; // '-' tile
    // Tile tile_2{contraption[65]}; // '/' tile
    // Tile tile_3{contraption[5]}; // '|' tile
    // Tile tile_4{contraption[14]}; // '\' tile
    // Tile tile_5{contraption[39]}; // '.' tile

    CHECK(contraption.size() == puzzle_test_data.size() * puzzle_test_data[0].size());
    CHECK(tile_1.energised == false);
    // CHECK_THAT(tile_1.enter_north, Catch::Matchers::Equals( Exits({11, 13})));
    // CHECK_THAT(tile_1.enter_east, Catch::Matchers::Equals( Exits({11})));

   }
    SECTION("check the tracing of the light beam") {
      Contraption contraption{build_contraption(puzzle_test_data)};

      do_light_beam(contraption);
      draw_energised(contraption);

      CHECK(calc_max(contraption) == 46);
      CHECK(find_max_tile_energisation(contraption, puzzle_test_data.size(), puzzle_test_data[0].size()) == 51);
      
    }
}
