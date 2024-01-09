#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

#include <2023_day11.hpp>

TEST_CASE(" 2023 day11 testing", "[day11]")
{
  std::string data_file = CURRENT_LIST_DIR;
  data_file += "/test.txt";

  AoCLib::char_data puzzle_test_data{ AoCLib::vectorise_char_data(data_file) };


  SECTION("check universe expansion")
  {
    Universe universe{ puzzle_test_data };

    expand_universe(universe);

    CHECK(universe.size() == 12);
    CHECK(universe[0].size() == 13);
    std::vector<char> row_3{ '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.' };

    std::vector<char> row_11{ '#', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.' };
    CHECK_THAT(universe[3], Catch::Matchers::Equals(row_3));
    CHECK_THAT(universe[11], Catch::Matchers::Equals(row_11));
  }

  SECTION("check determination of galaxies")
  {
    Universe universe{ puzzle_test_data };
    expand_universe(universe);
    Galaxies galaxies{ get_galaxies(universe) };

    CHECK(galaxies.size() == 9);
    CHECK(galaxies.front().first == 1);
    CHECK(galaxies.back().first == 9);
    CHECK(galaxies[3].second == std::pair<size_t, size_t>(5, 8));
  }

  SECTION("check creation of galaxy pairs")
  {
    Universe universe{ puzzle_test_data };
    expand_universe(universe);
    dump_universe(universe);

    Galaxies galaxies{ get_galaxies(universe) };
    GalaxyPairs pairs{ pair_galaxies(galaxies) };

    CHECK(pairs.size() == 36);
    CHECK(pairs[35] == GalaxyPair(7, 8));
    dump_universe(universe);
  }

  SECTION("check the calculation of the total distnaces")
  {

    Universe universe{ puzzle_test_data };
    const Galaxies original_galaxies(get_galaxies(universe));
    const GalaxyPairs pairs(pair_galaxies(original_galaxies));
    expand_universe(universe);
    const Galaxies galaxies(get_galaxies(universe));
    int original_separation{calculate_galaxy_manhattan_seperation(pairs, original_galaxies)};
    int increased_separation{calculate_galaxy_manhattan_seperation(pairs, galaxies)};
    CHECK(increased_separation == 374);
    int separation_change {increased_separation - original_separation};
    int ten_times_separtaion = separation_change * 10 + original_separation - separation_change;
    CHECK(ten_times_separtaion == 1030);
    int hundred_times_separation = (separation_change * 100 + original_separation - separation_change);
    CHECK(hundred_times_separation == 8410);


  }
}