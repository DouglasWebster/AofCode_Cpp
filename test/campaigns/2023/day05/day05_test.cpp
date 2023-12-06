#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>

#include <2023_day05.hpp>

// start with a test case that does nothing but fail.

TEST_CASE(" 2023 day05 ", "[day05]")
{
  std::stringstream tmp_file;
  tmp_file << std::tmpnam(nullptr) << "_2023_day04.txt";// NOLINT: This is not thread safe!

  std::string test_data = "seeds: 79 14 55 13\n";
  test_data += "\n";
  test_data += "seed-to-soil map:\n";
  test_data += "50 98 2\n";
  test_data += "52 50 48\n";
  test_data += "\n";
  test_data += "soil-to-fertilizer map:\n";
  test_data += "0 15 37\n";
  test_data += "37 52 2\n";
  test_data += "39 0 15\n";
  test_data += "\n";
  test_data += "fertilizer-to-water map:\n";
  test_data += "49 53 8\n";
  test_data += "0 11 42\n";
  test_data += "42 0 7\n";
  test_data += "57 7 4\n";
  test_data += "\n";
  test_data += "water-to-light map:\n";
  test_data += "88 18 7\n";
  test_data += "18 25 70\n";
  test_data += "\n";
  test_data += "light-to-temperature map:\n";
  test_data += "45 77 23\n";
  test_data += "81 45 19\n";
  test_data += "68 64 13\n";
  test_data += "\n";
  test_data += "temperature-to-humidity map:\n";
  test_data += "0 69 1\n";
  test_data += "1 0 69\n";
  test_data += "\n";
  test_data += "humidity-to-location map:\n";
  test_data += "60 56 37\n";
  test_data += "56 93 4";

  std::ofstream test_file{ tmp_file.str() };
  if (!test_file) {
    std::cerr << "Test file " << tmp_file.str() << "could not be opened for writing\n";
  }

  test_file << test_data << std::flush;

  AoCLib::line_data puzzle_test_data{ AoCLib::vectorise_line_data(tmp_file.str()) };

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

    RangeMap new_map{adjust_mapping(source_ranges, range_map)};
  }

  // clean up after each test
  std::filesystem::path temp_file_path = tmp_file.str();
  if (std::filesystem::exists(temp_file_path)) { std::filesystem::remove(temp_file_path); }
}
