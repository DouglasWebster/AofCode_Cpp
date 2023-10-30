#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include <iostream>

#include <2022_day20.hpp>

// start with a test case that does nothing but fail.

TEST_CASE(" part 1", "[day20]")
{
  Items test_items_1{ Item(2, false),
    Item(1, false),
    Item(5, false),
    Item(-4, false),
    Item(0, false),
    Item(9, false),
    Item(-12, false),
    Item(8, false) };

  Items result_items_1{ Item(1, true),
    Item(8, true),
    Item(-12, true),
    Item(2, true),
    Item(0, true),
    Item(5, true),
    Item(-4, true),
    Item(9, true) };

  Items test_items_2{ Item(1, false),
    Item(2, false),
    Item(-3, false),
    Item(3, false),
    Item(-2, false),
    Item(0, false),
    Item(4, false) };

  Items result_items_2{ Item(1, true),
    Item(2, true),
    Item(-3, true),
    Item(4, true),
    Item(0, true),
    Item(3, true),
    Item(-2, true) };

  SECTION("check moves")
  {
    make_moves(test_items_1);
    std::cout << "result : {";
    for (auto item : test_items_1) { std::cout << item.first << ", "; }
    std::cout << "\b\b}\n";
    CHECK_THAT(test_items_1, Catch::Matchers::Equals(result_items_1));

    CHECK(calculate_coordinate_sum(test_items_1) == 0);

    make_moves(test_items_2);
    std::cout << "result : {";
    for (auto item : test_items_2) { std::cout << item.first << ", "; }
    std::cout << "\b\b}\n";
    CHECK_THAT(test_items_2, Catch::Matchers::Equals(result_items_2));

    CHECK(calculate_coordinate_sum(test_items_2) == 3);
  }
}
