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

    CHECK(map_extent.first.first == 2);
    CHECK(map_extent.first.second == 3);
    CHECK(map_extent.second.first == 7);
    CHECK(map_extent.second.second == 7);
  }

  SECTION("check next map creation")
  {
    GroveMap next_map{ create_next_map(initial_map) };

    CHECK(next_map.size() == 9);
    CHECK(next_map[0].size() == 9);
    CHECK(next_map[0][0] == '.')  ;
    CHECK(next_map[8][8] == '.');
    CHECK(next_map[3][1] == '#');
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

  SECTION("check movement maps are marked correctly")
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

    std::vector<std::string> result_data{ { "...AA.." },
      { "...##.." },
      { "..#...." },
      { "..A..N." },
      { "......." },
      { "...N..." },
      { "......." } };

    GroveMap result_map{};
    for (auto row : result_data) {
      result_map.push_back(std::vector<char>{ row.begin(), row.end() });
    }

    MovementMap movement_map{ mark_allowable_positions(check_map, Direction::north) };

    CHECK_THAT(check_map, Catch::Matchers::Equals(result_map));
    CHECK(movement_map[1][3] == Direction::north);
    CHECK(movement_map[1][4] == Direction::north);
    CHECK(movement_map[2][2] == Direction::south);
    CHECK(movement_map[3][6] == Direction::stay_put);
    CHECK(movement_map[5][3] == Direction::stay_put);
  }

  SECTION("check movement and space counting")
  {
    GroveMap grove_map{ create_next_map(initial_map) };
    MovementMap move_map{ mark_allowable_positions(grove_map, Direction::north) };

    do_movement(grove_map, move_map);

    std::cout << "pass 1" << '\n';
      for(auto row: grove_map) {
        for(auto item : row) {
          std::cout << item;
        }
        std::cout << '\n';
      }
      std::cout << '\n';

    std::vector<std::string> first_result_data{ ".....#...",
      "...#...#.",
      ".#..#.#..",
      ".....#..#",
      "..#.#.##.",
      "#..#.#...",
      "#.#.#.##.",
      ".........",
      "..#..#..." };

    GroveMap first_result_map{};
    for (auto row : first_result_data) {
      first_result_map.push_back(std::vector<char>{ row.begin(), row.end() });
    }

    CHECK_THAT(grove_map, Catch::Matchers::Equals(first_result_map));

    auto prefered_direction{Direction::north};
    for(auto counter{0}; counter < 10; ++counter){
      switch (prefered_direction)
      {
      case Direction::north:
        prefered_direction = Direction::south;
        break;
      case Direction::south:
        prefered_direction = Direction::west;
        break;
      case Direction::west:
        prefered_direction = Direction::east;
        break;
      case Direction::east:
        prefered_direction = Direction::north;
        break;     
      default:
        break;
      }

      MovementMap movement_map{mark_allowable_positions(grove_map, prefered_direction)};
      do_movement(grove_map, movement_map);
      std::cout << "pass " << counter +2 << '\n';
      for(auto row: grove_map) {
        for(auto item : row) {
          std::cout << item;
        }
        std::cout << '\n';
      }
      std::cout << '\n';
    }

    int empty_spaces{count_empty_ground(grove_map)};

    CHECK(empty_spaces == 110);
  }
}
