#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include <iostream>

#include <2022_day01.hpp>


bool areVectorsEqual(const std::vector<std::vector<int>> &a, const std::vector<std::vector<int>> &b) { return a == b; }


TEST_CASE(" collate elven pack calories", "[day01]")
{

  std::vector<std::vector<int>> test_data{
    { 1000 }, { 2000 }, { 3000 }, {}, { 4000 }, {}, { 5000 }, { 6000 }, {}, { 7000 }, { 8000 }, { 9000 }, {}, { 10000 }
  };

  std::vector<std::vector<int>> test_result {{ 1000, 2000, 3000 }, { 4000 }, { 5000, 6000 }, { 7000, 8000, 9000 }, { 10000 }};

  ElvenPacks empty_pack{};
  using Catch::Matchers::IsEmpty;

  SECTION("an empty set of vectors returns an empty vector ")
  {
    REQUIRE_THAT(collate_calories(empty_pack), IsEmpty());
    REQUIRE_THAT(collate_calories(std::vector<std::vector<int>>{ {} }), IsEmpty());
  }

  SECTION("only zero or one item per vector allowed")
  {
    REQUIRE_THAT(collate_calories(ElvenPacks{ { 1, 2 } }), IsEmpty());
    REQUIRE_THAT(collate_calories(ElvenPacks{ { 1 }, { 2 } }), !IsEmpty());
  }

  SECTION("a stream of vectors with values returns a single vector with the values as items")
  {
    std::vector<std::vector<int>> vector_stream{ { 1 }, { 2 }, { 3 }, { 2 }, { 1 } };
    const std::vector<std::vector<int>> vector_result{ { { 1, 2, 3, 2, 1 } } };
    auto call_result{ collate_calories(vector_stream) };

    REQUIRE(areVectorsEqual(call_result, vector_result));
  }

  SECTION("empty vectors should be dropped and initiate a new elves item vector.")
  {
    std::vector<std::vector<int>> vector_stream{ { 1 }, {}, { 2 }, { 3 }, { 2 }, { 1 } };
    const std::vector<std::vector<int>> vector_result{ { { 1 }, {2, 3, 2, 1 } } };
    auto call_result{ collate_calories(vector_stream) };

    REQUIRE(areVectorsEqual(call_result, vector_result));
  }

  SECTION("test data should create the 5 vectors of test result") {

    auto call_result {collate_calories(test_data)};
    REQUIRE(areVectorsEqual(call_result, test_result));

  }
}

TEST_CASE(" sum the contents of each pack", "[day01]") {
  std::vector<std::vector<int>> pack_contents {{ 1000, 2000, 3000 }, { 4000 }, { 5000, 6000 }, { 7000, 8000, 9000 }, { 10000 }};
  std::vector<int> pack_calories{6000, 4000, 11000, 24000, 10000};

  REQUIRE_THAT(sum_calories(pack_contents), Catch::Matchers::Equals(pack_calories));
}

TEST_CASE(" get the max values " "day01") {
  std::vector<int> pack_calories{6000, 4000, 11000, 24000, 10000};

  SECTION(" empty packs return 0 as a max calorie count"){
    REQUIRE(max_values(std::vector<int>{}, 2) == 0);
  }

  SECTION(" finding the max of 0 packs returns 0 as the max calorie count"){
    REQUIRE(max_values(pack_calories, 0) == 0);
  }

  SECTION(" of a single pack") {
    REQUIRE(max_values(pack_calories, 1) == 24000);
  }

  SECTION(" of multiple packs") {
    REQUIRE(max_values(pack_calories, 2) == 35000);
    REQUIRE(max_values(pack_calories, 3) == 45000);
  }
}
