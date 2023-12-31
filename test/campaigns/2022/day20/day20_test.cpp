#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include <iostream>

#include <2022_day20.hpp>

// start with a test case that does nothing but fail.

TEST_CASE(" setup", "[day20]")
{
  AoCLib::int_data data{ { 1 }, { 5 }, { -4 }, { 0 }, { 9 }, { -12 }, { 8 } };

  auto [items, locations] = create_item_vectors(data);

  CHECK(items.size() == data.size());
  CHECK(items.back().first == data.back()[0]);
}

TEST_CASE(" part 1", "[day20]")
{
  Items test_items_1{ Item(2, 0),
    Item(1, 1),
    Item(5, 2),
    Item(-4, 3),
    Item(0, 4),
    Item(9, 5),
    Item(-12, 6),
    Item(8, 7) };

  Locations locations_1{ 0, 1, 2, 3, 4, 5, 6, 7 };

  Items result_items_1{ Item(1, 1),
    Item(8, 7),
    Item(-12, 6),
    Item(2, 0),
    Item(0, 4),
    Item(5, 2),
    Item(-4, 3),
    Item(9, 5) };

  Items test_items_2{
    Item(1, 0), Item(2, 1), Item(-3, 2), Item(3, 3), Item(-2, 4), Item(0, 5), Item(4, 6)
  };

  Locations locations_2{ 0, 1, 2, 3, 4, 5, 6 };

  Items result_items_2{
    Item(1, 0), Item(2, 1), Item(-3, 2), Item(4, 6), Item(0, 5), Item(3, 3), Item(-2, 4)
  };

  SECTION("check moves")
  {
    make_moves(test_items_1, locations_1);
    CHECK_THAT(test_items_1, Catch::Matchers::Equals(result_items_1));

    CHECK(calculate_coordinate_sum(test_items_1) == 0);

    make_moves(test_items_2, locations_2);
    CHECK_THAT(test_items_2, Catch::Matchers::Equals(result_items_2));

    CHECK(calculate_coordinate_sum(test_items_2) == 3);
  }
}

TEST_CASE(" part 2", "day20")
{
    REQUIRE( true );
}
