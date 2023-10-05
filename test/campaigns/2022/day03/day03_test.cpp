#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include <iostream>

#include <2022_day03.hpp>

TEST_CASE(" check getting contents", "[day03]") {
  AoCLib::str_data test_data {};
    CHECK(collate_contents(test_data).empty());
    test_data.push_back({""});
    Contents data_vector{{""}};
    CHECK_THAT(collate_contents(test_data), Catch::Matchers::Equals(data_vector));
    test_data.clear();
    test_data.push_back({{"ABC"}, {""}});
    data_vector.clear();
    data_vector.push_back({"ABC"});
    CHECK_THAT(collate_contents(test_data), Catch::Matchers::Equals(data_vector));
    test_data.push_back({{"DEF"}, {"GHI"}});
    data_vector.push_back({"DEF"});
    test_data.push_back({{"KLM"}});
    data_vector.push_back({"KLM"});
    CHECK_THAT(collate_contents(test_data), Catch::Matchers::Equals(data_vector));
}

TEST_CASE(" check rucksack contents", "[day03]")
{
  CHECK(get_compartments({""}) == Rucksack{ "", "" });
  CHECK(get_compartments("ABC") == Rucksack("", ""));
  CHECK(get_compartments("vJrwpWtwJgWrhcsFMMfFFhFp") == Rucksack("vJrwpWtwJgWr", "hcsFMMfFFhFp"));
  CHECK(get_compartments("jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL") == Rucksack("jqHRNqRjqzjGDLGL", "rsFMfFZSrLrFZsSL"));
  CHECK(get_compartments("PmmdzqPrVvPwwTWBwg") == Rucksack("PmmdzqPrV", "vPwwTWBwg"));
}

TEST_CASE(
  " check common item"
  "[day03]")
{
  SECTION(" returns the correct item")
  {
    CHECK(find_common_item(Rucksack{ "", "" }) == 0);
    CHECK(find_common_item(Rucksack{ "abc", "def" }) == 0);
    CHECK(find_common_item(Rucksack{ "vJrwpWtwJgWr", "hcsFMMfFFhFp" }) == 'p');
    CHECK(find_common_item(Rucksack{ "jqHRNqRjqzjGDLGL", "rsFMfFZSrLrFZsSL" }) == 'L');
  }

  SECTION(" calculates the correct priority")
  {
    CHECK(calculate_priority('p') == 16);
    CHECK(calculate_priority('L') == 38);
    CHECK(calculate_priority('P') == 42);
    CHECK(calculate_priority('v') == 22);
    CHECK(calculate_priority('t') == 20);
  }
}

TEST_CASE(" check badge priorities", "[day03]") {
  Contents test_contents{{{""}, {""}, {""}}};
  CHECK(calculate_badges(test_contents) == 0);
  
  test_contents.push_back({"vJrwpWtwJgWrhcsFMMfFFhFp"});
  test_contents.push_back({"jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL"});
  test_contents.push_back({"PmmdzqPrVvPwwTWBwg"});
  CHECK(calculate_badges(test_contents) == 18);

  test_contents.push_back({"wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn"});
  test_contents.push_back({"ttgJtRGJQctTZtZT"});
  test_contents.push_back({"CrZsJsPPZsGzwwsLwLmpwMDw"});
  CHECK(calculate_badges(test_contents) == 70);
}
