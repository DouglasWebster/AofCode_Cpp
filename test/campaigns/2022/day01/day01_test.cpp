#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include <2022_day01.hpp>

TEST_CASE(" collate elven pack calories", "[collate]")
{

  ElvenPacks empty_pack{};
  using Catch::Matchers::IsEmpty;

  SECTION("an empty set of vectors returns an empty vector ")
  {
    REQUIRE_THAT(collate_calories(empty_pack), IsEmpty());
  }

  // SECTION("a file with no data returns a single empty vector")
  // {
  //   const std::ofstream test_file{ tmp_file.str() };
  //   if (!test_file) { std::cerr << "Test file " << tmp_file.str() << "could not be opened for writing\n"; }

  //   const AoCLib::int_data no_data_vector{ {} };
  //   REQUIRE_THAT(AoCLib::vectorise_int_data(tmp_file.str()), Catch::Matchers::Equals(no_data_vector));
  // }

  // SECTION("a file with a single line of data returns a single vector")
  // {
  //   std::ofstream test_file{ tmp_file.str() };
  //   const std::string test_data{ "1, 2, 3" };

  //   if (!test_file) { std::cerr << "Test file " << tmp_file.str() << "could not be opened for writing\n"; }

  //   test_file << test_data << std::flush;
  //   const AoCLib::int_data data_vector{ { 1, 2, 3 } };
  //   REQUIRE_THAT(AoCLib::vectorise_int_data(tmp_file.str()), Catch::Matchers::Equals(data_vector));
  // }
}
