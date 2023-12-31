#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

#include <2023_day15.hpp>

TEST_CASE(" 2023 day15 testing", "[day15]")
{
  std::string data_file = CURRENT_LIST_DIR;
  data_file += "/test.txt";

  AoCLib::line_data puzzle_test_data{ AoCLib::vectorise_line_data(data_file) };


  SECTION("check conversion to has steps")
  {
    Sequence sequence{ AoCLib::split_string_at_delimter(puzzle_test_data[0], ',') };

    CHECK(sequence.size() == 11);
    CHECK(sequence[0] == "rn=1");
    CHECK(sequence[10] == "ot=7");
  }

  SECTION("check the hashing algoritm")
  {
    Sequence sequence{ AoCLib::split_string_at_delimter(puzzle_test_data[0], ',') };

    CHECK(hash_step(sequence[0]) == 30);
    CHECK(hash_step(sequence[1]) == 253);
    CHECK(hash_step(sequence[2]) == 97);
    CHECK(hash_step(sequence[3]) == 47);
    CHECK(hash_step(sequence[4]) == 14);
    CHECK(hash_step(sequence[5]) == 180);
    CHECK(hash_step(sequence[6]) == 9);
    CHECK(hash_step(sequence[7]) == 197);
    CHECK(hash_step(sequence[8]) == 48);
    CHECK(hash_step(sequence[9]) == 214);
    CHECK(hash_step(sequence[10]) == 231);
  }

  SECTION("check summation of results")
  {

    Sequence sequence{ AoCLib::split_string_at_delimter(puzzle_test_data[0], ',') };
    size_t total{};

    for (const auto &step : sequence) { total += hash_step(step); }

    CHECK(total == 1320);
  }

  SECTION("check hashing of HashMap")
  {
    HashMap hash_map{ create_hashmap(AoCLib::line_data({ "rn=1" })) };

    CHECK(hash_map[0].size() == 1);
    hash_map = create_hashmap(AoCLib::line_data({ "rn=1", "cm-" }));
    CHECK(hash_map[0].size() == 1);

    hash_map = create_hashmap(puzzle_test_data);
    CHECK(hash_map[0].size() == 2);
    CHECK(hash_map[3].size() == 3);
    
  }

  SECTION ("check focusing power calculation") {
    HashMap hash_map{create_hashmap(puzzle_test_data)};
    CHECK(calc_focusing_power(hash_map ) == 145);
  }
}
