#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>

#include <2023_day05.hpp>
#include <iostream>

// start with a test case that does nothing but fail.

TEST_CASE(" 2023 day05 ", "[day05]")
{
  std::string data_file = CURRENT_LIST_DIR;
  data_file += "/test.txt";

  AoCLib::line_data puzzle_test_data{ AoCLib::vectorise_line_data(data_file)};

  SECTION("check building seed vector")
  {
    CHECK_THAT(
      build_seeds_vector(puzzle_test_data[0]), Catch::Matchers::Equals(Seeds{ 79, 14, 55, 13 }));
  }

  SECTION("check creation of a GardenMap")
  {

    RangeMap map{};

    CHECK(build_map(map, puzzle_test_data, 3) == 5);

    Mapping section_1{ map[0] };
    CHECK(section_1.first == GardenRange{ 0, 49 });
    CHECK(section_1.second == section_1.first);

    Mapping section_2{ map[1] };
    CHECK(section_2.first == GardenRange{ 50, 97 });
    CHECK(section_2.second == GardenRange{ 52, 99 });
  }

  SECTION("check building the catagories vector")
  {
    Catagories catagories{ build_catagories(puzzle_test_data) };

    CHECK(catagories.size() == 7);
    CHECK(catagories[0].size() == 4);
    CHECK(catagories[1].size() == 4);
    CHECK(catagories[2].size() == 5);
    CHECK(catagories[3].size() == 4);
    CHECK(catagories[4].size() == 5);
    CHECK(catagories[5].size() == 3);
    CHECK(catagories[6].size() == 4);
  }

  SECTION("check tracing of a seed path")
  {
    Catagories catagories{ build_catagories(puzzle_test_data) };

    CHECK(trace_seed(79, catagories) == 82);
    CHECK(trace_seed(14, catagories) == 43);
    CHECK(trace_seed(55, catagories) == 86);
    CHECK(trace_seed(13, catagories) == 35);
  }

  SECTION("check creation of seed ranges")
  {
    SourceRanges seed_ranges{ build_seed_ranges(puzzle_test_data[0]) };

    CHECK(seed_ranges.size() == 2);
    CHECK(seed_ranges[0] == GardenRange{ 55, 67 });
    CHECK(seed_ranges[1] == GardenRange{ 79, 92 });
  }

  SECTION("check adjustment of level ranges")
  {
    RangeMap range_map{};
    build_map(range_map, puzzle_test_data, 3);

    SourceRanges source_ranges{build_seed_ranges(puzzle_test_data[0])};
    Catagories catagories{build_catagories(puzzle_test_data)};

    for(const auto &catagory : catagories) {
      adjust_mapping(source_ranges, catagory);
    }

    CHECK(source_ranges.front().first == 46);

  
  }

}
