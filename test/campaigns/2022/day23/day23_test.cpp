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

  SECTION("check map extent calculation")
  {
    GroveExtent map_extent{ get_map_extent(initial_map) };

    CHECK(map_extent.first.first == 3);
    CHECK(map_extent.first.second == 2);
    CHECK(map_extent.second.first == 7);
    CHECK(map_extent.second.second == 7);
  }

  SECTION("check next map creation")
  {
    GroveMap next_map{ create_next_map(initial_map) };

    CHECK(next_map.size() == 9);
    CHECK(next_map[0].size() == 9);
    // CHECK(next_map[0][0] == ' ')  ;
    // CHECK(next_map[8][8] == ' ');
    // CHECK(next_map[3][1] == '#');
  }

  SECTION("check allowable move directions")
  {
    std::vector<std::string> check_data{ { "......." },
      { "...##.." },
      { "..#...." },
      { ".....#." },
      { "......." },
      { "...#..." },
      { "......." } };

    GroveMap check_map{};
    for (auto row : check_data) {
      check_map.push_back(std::vector<char>{ row.begin(), row.end() });
    }

    CHECK(which_directions(check_map, { 1, 1 }) == 0);
    CHECK(which_directions(check_map, { 1, 3 }) == static_cast<int>(Direction::north));
    CHECK(which_directions(check_map, { 1, 4 })
          == static_cast<int>(Direction::north) + static_cast<int>(Direction::east)
               + static_cast<int>(Direction::south));
    CHECK(which_directions(check_map, { 3, 5 })
          == static_cast<int>(Direction::north) + static_cast<int>(Direction::east)
               + static_cast<int>(Direction::south) + static_cast<int>(Direction::west));
  }
}
