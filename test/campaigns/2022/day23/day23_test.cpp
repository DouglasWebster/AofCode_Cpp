#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include <iostream>

#include <2022_day23.hpp>

// start with a test case that does nothing but fail.

TEST_CASE(" 2022 day23 testing not started", "[day23]")
{

  std::vector<std::string> test_data{ { ".............." },
    { ".............." },
    { ".......#......" },
    { ".....###.#...." },
    { "...#...#.#...." },
    { "....#...##...." },
    { "...#.###......" },
    { "...##.#.##...." },
    { "....#..#......" },
    { ".............." },
    { ".............." },
    { ".............." } };

  GroveMap initial_map{};

  for (auto row : test_data) { initial_map.push_back(std::vector<char>{ row.begin(), row.end() }); }

  REQUIRE(true);
}
