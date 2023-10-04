#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include <iostream>

#include <2022_day02.hpp>

// start with a test case that does nothing but fail.

TEST_CASE(" collate strategy", "[day02]")
{
    AoCLib::str_data test_data {{"A", "Y"}, {"B", "X"}, {"C", "Z"} };
    const strategy moves {collate_moves(test_data)};

    REQUIRE((moves[0].first == "A" && moves[2].second == "Z"));
}

TEST_CASE(" calculate first strategy", "[day02]") {
    CHECK(first_strategy(std::make_pair("A", "Y")) == 8);
    CHECK(first_strategy(std::make_pair("B", "X")) == 1);
    CHECK(first_strategy(std::make_pair("C", "Z")) == 6);

}

TEST_CASE(" calculate second strategy", "[day02]") {
    CHECK(second_strategy(std::make_pair("A", "Y")) == 4);
    CHECK(second_strategy(std::make_pair("B", "X")) == 1);
    CHECK(second_strategy(std::make_pair("C", "Z")) == 7);

}