#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

#include <2023_day12.hpp>

TEST_CASE(" 2023 day12 testing", "[day12]")
{

  SECTION("check removal of tail of Springs") {
    const Springs springs{"?#?#?#?#?#?#?#?"};
    const DamagedGroups groups{1, 3, 1, 6};

    CHECK(first_item_fits(springs,groups) == 1);
  }
}