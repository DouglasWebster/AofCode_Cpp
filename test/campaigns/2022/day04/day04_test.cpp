#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include <iostream>

#include <2022_day04.hpp>

// We assume that the data raw data has been split into a vector of vectors strings
// of the form {{"1-2"},{"3-4"}},{{"5-6"},{"7-8"}}...

TEST_CASE(" check assignments are created correctly", "[day04]")
{

  CHECK_THAT(collate_assignments({}), Catch::Matchers::IsEmpty());
  CHECK_THAT(collate_assignments({ { "" } }), Catch::Matchers::IsEmpty());

  AoCLib::str_data test_data{ { { "5-7" }, { "8-9" } } };
  Assignments result{ { { { 5, 7 }, { 8, 9 } } } };
  CHECK_THAT(collate_assignments(test_data), Catch::Matchers::Equals(result));

  SECTION(" make sure it ignores incorrectly formatted pairs")
  {
    test_data.push_back({ {} });
    CHECK_THAT(collate_assignments(test_data), Catch::Matchers::Equals(result));
    test_data.pop_back();
    test_data.push_back({ { "12-13" }, { "24-25" }, { "36-37" } });
    CHECK_THAT(collate_assignments(test_data), Catch::Matchers::Equals(result));
  }

  test_data.pop_back();
  test_data.push_back({ { "2-8" }, { "3-7" } });
  result.push_back(std::make_pair(std::make_pair(2, 8), std::make_pair(3, 7)));
  test_data.push_back({ { "6-6" }, { "4-6" } });
  result.push_back(std::make_pair(std::make_pair(6, 6), std::make_pair(4, 6)));
  test_data.push_back({ { "2-6" }, { "4-8" } });
  result.push_back(std::make_pair(std::make_pair(2, 6), std::make_pair(4, 8)));
  CHECK_THAT(collate_assignments(test_data), Catch::Matchers::Equals(result));
}

TEST_CASE(" check fully contains", "[day04]") {
    Assignment assignment{}; // empty ranges are fully contained!
    CHECK(contains_fully(assignment) == true);

    assignment.first.first = 2;
    assignment.first.second = 4;
    assignment.second.first = 6;
    assignment.second.second = 8;
    CHECK(contains_fully(assignment) == false);

    assignment.first.first = 2;
    assignment.first.second = 8;
    assignment.second.first = 3;
    assignment.second.second = 7;
    CHECK(contains_fully(assignment) == true);

    assignment.first.first = 6;
    assignment.first.second = 6;
    assignment.second.first = 3;
    assignment.second.second = 7;
    CHECK(contains_fully(assignment) == true);

    assignment.first.first = 6;
    assignment.first.second = 8;
    assignment.second.first = 2;
    assignment.second.second = 6;
    CHECK(contains_fully(assignment) == false);

}

TEST_CASE(" checks overlapping" "[day04]")
{
    Assignment assignment{};
    CHECK(overlapping(assignment) == true);

    assignment.first.first = 2;
    assignment.first.second = 4;
    assignment.second.first = 6;
    assignment.second.second = 8;
    CHECK(overlapping(assignment) == false);

    assignment.first.first = 2;
    assignment.first.second = 3;
    assignment.second.first = 4;
    assignment.second.second = 5;
    CHECK(overlapping(assignment) == false);

    assignment.first.first = 5;
    assignment.first.second = 7;
    assignment.second.first = 7;
    assignment.second.second = 9;
    CHECK(overlapping(assignment) == true);

    assignment.first.first = 2;
    assignment.first.second = 8;
    assignment.second.first = 4;
    assignment.second.second = 7;
    CHECK(overlapping(assignment) == true);

    assignment.first.first = 6;
    assignment.first.second = 6;
    assignment.second.first = 4;
    assignment.second.second = 6;
    CHECK(overlapping(assignment) == true);

    assignment.first.first = 2;
    assignment.first.second = 6;
    assignment.second.first = 4;
    assignment.second.second = 8;
    CHECK(overlapping(assignment) == true);
}