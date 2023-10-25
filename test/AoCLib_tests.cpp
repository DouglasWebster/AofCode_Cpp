#define _CRT_SECURE_NO_WARNINGS

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>


#include <AofCode_Cpp/aoc_library.hpp>


#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <memory>
#include <sstream>


TEST_CASE(" Vectorise integer data", "[vectorise]")
{
  using Catch::Matchers::IsEmpty;
  auto empty_vector = std::vector<std::vector<int>>{};

  std::stringstream tmp_file;
  tmp_file << std::tmpnam(nullptr) << "_AoCLibTest.txt";// NOLINT: This is not thread safe!

  SECTION("an empty or invalid file name returns and empty vector ")
  {
    REQUIRE_THAT(AoCLib::vectorise_int_data(""), IsEmpty());
    REQUIRE_THAT(AoCLib::vectorise_int_data(tmp_file.str()), Catch::Matchers::IsEmpty());
  }

  SECTION("a file with no data returns a single empty vector")
  {
    const std::ofstream test_file{ tmp_file.str() };
    if (!test_file) {
      std::cerr << "Test file " << tmp_file.str() << "could not be opened for writing\n";
    }

    const AoCLib::int_data no_data_vector{ {} };
    REQUIRE_THAT(
      AoCLib::vectorise_int_data(tmp_file.str()), Catch::Matchers::Equals(no_data_vector));
  }

  SECTION("a file with a single line of data returns a single vector")
  {
    std::ofstream test_file{ tmp_file.str() };
    const std::string test_data{ "1, 2, 3" };

    if (!test_file) {
      std::cerr << "Test file " << tmp_file.str() << "could not be opened for writing\n";
    }

    test_file << test_data << std::flush;
    const AoCLib::int_data data_vector{ { 1, 2, 3 } };
    REQUIRE_THAT(AoCLib::vectorise_int_data(tmp_file.str()), Catch::Matchers::Equals(data_vector));
  }

  SECTION("separators can be either space of comma")
  {
    std::ofstream test_file{ tmp_file.str() };
    const std::string space_test_data{ "1 2 3" };

    if (!test_file) {
      std::cerr << "Test file " << tmp_file.str() << "could not be opened for writing\n";
    }

    test_file << space_test_data << std::flush;
    const AoCLib::int_data data_vector{ { 1, 2, 3 } };
    REQUIRE_THAT(AoCLib::vectorise_int_data(tmp_file.str()), Catch::Matchers::Equals(data_vector));
  }

  SECTION("empty lines are returned as empty vectors")
  {

    std::ofstream test_file{ tmp_file.str() };
    std::string test_data{ "" };

    if (!test_file) {
      std::cerr << "Test file " << tmp_file.str() << "could not be opened for writing\n";
    }

    test_file << test_data << std::flush;
    AoCLib::int_data data_vector{ {} };
    REQUIRE_THAT(AoCLib::vectorise_int_data(tmp_file.str()), Catch::Matchers::Equals(data_vector));

    test_data.append(" ");
    test_file << test_data << std::flush;
    REQUIRE_THAT(AoCLib::vectorise_int_data(tmp_file.str()), Catch::Matchers::Equals(data_vector));

    test_data.append("\n1, 2,3\n ");
    test_file << test_data << std::flush;
    data_vector.clear();
    data_vector.push_back({});
    data_vector.push_back({ 1, 2, 3 });
    data_vector.push_back({});
    REQUIRE_THAT(AoCLib::vectorise_int_data(tmp_file.str()), Catch::Matchers::Equals(data_vector));
  }

  // clean up after each test
  std::filesystem::path temp_file_path = tmp_file.str();
  if (std::filesystem::exists(temp_file_path)) { std::filesystem::remove(temp_file_path); }
}

TEST_CASE(" Vectorise string data", "[vectorise]")
{
  using Catch::Matchers::IsEmpty;
  auto empty_vector = std::vector<std::vector<std::string>>{};
  std::stringstream tmp_file;
  tmp_file << std::tmpnam(nullptr) << "_AoCLibTest.txt";// NOLINT: This is not thread safe!

  SECTION("an empty or invalid file name returns and empty vector ")
  {
    REQUIRE_THAT(AoCLib::vectorise_string_data(""), IsEmpty());
    REQUIRE_THAT(AoCLib::vectorise_string_data(tmp_file.str()), Catch::Matchers::IsEmpty());
  }

  SECTION("a file with no data returns a single empty vector")
  {
    const std::ofstream test_file{ tmp_file.str() };
    if (!test_file) {
      std::cerr << "Test file " << tmp_file.str() << "could not be opened for writing\n";
    }

    const AoCLib::str_data no_data_vector{ {} };
    REQUIRE_THAT(
      AoCLib::vectorise_string_data(tmp_file.str()), Catch::Matchers::Equals(no_data_vector));
  }

  SECTION("a file with a single line of data returns a single vector")
  {
    std::ofstream test_file{ tmp_file.str() };
    const std::string test_data{ "A, B, C" };

    if (!test_file) {
      std::cerr << "Test file " << tmp_file.str() << "could not be opened for writing\n";
    }

    test_file << test_data << std::flush;
    const AoCLib::str_data data_vector{ { "A", "B", "C" } };
    REQUIRE_THAT(
      AoCLib::vectorise_string_data(tmp_file.str(), ','), Catch::Matchers::Equals(data_vector));
  }

  SECTION("separators can be either space of comma")
  {
    std::ofstream test_file{ tmp_file.str() };
    const std::string space_test_data{ "A B C" };

    if (!test_file) {
      std::cerr << "Test file " << tmp_file.str() << "could not be opened for writing\n";
    }

    test_file << space_test_data << std::flush;
    const AoCLib::str_data data_vector{ { "A", "B", "C" } };
    REQUIRE_THAT(
      AoCLib::vectorise_string_data(tmp_file.str()), Catch::Matchers::Equals(data_vector));
  }

  SECTION("empty lines are returned as vectors with empty strings")
  {

    std::ofstream test_file{ tmp_file.str() };
    std::string test_data{ "" };

    if (!test_file) {
      std::cerr << "Test file " << tmp_file.str() << "could not be opened for writing\n";
    }

    test_file << test_data << std::flush;
    AoCLib::str_data data_vector{ {} };
    REQUIRE_THAT(
      AoCLib::vectorise_string_data(tmp_file.str()), Catch::Matchers::Equals(data_vector));

    test_data.append(" ");
    test_file << test_data << std::flush;
    data_vector.clear();
    data_vector.push_back({ "" });
    REQUIRE_THAT(
      AoCLib::vectorise_string_data(tmp_file.str()), Catch::Matchers::Equals(data_vector));

    test_data.append("\nA, B, C\n ");
    test_file << test_data << std::flush;
    data_vector.push_back({ "A", "B", "C" });
    data_vector.push_back({ "" });
    REQUIRE_THAT(
      AoCLib::vectorise_string_data(tmp_file.str(), ','), Catch::Matchers::Equals(data_vector));

    test_data.clear();
    test_data.append("\nDEF,   IJK,   LMN");
    test_file << test_data << std::flush;
    data_vector.push_back({ "DEF", "IJK", "LMN" });

    REQUIRE_THAT(
      AoCLib::vectorise_string_data(tmp_file.str(), ','), Catch::Matchers::Equals(data_vector));
  }

  // clean up after each test
  std::filesystem::path temp_file_path = tmp_file.str();
  if (std::filesystem::exists(temp_file_path)) { std::filesystem::remove(temp_file_path); }
}

TEST_CASE(" Vectorise character data", "[vectorise]")
{
  using Catch::Matchers::IsEmpty;
  auto empty_vector = std::vector<std::vector<std::string>>{};
  std::stringstream tmp_file;
  tmp_file << std::tmpnam(nullptr) << "_AoCLibTest.txt";// NOLINT: This is not thread safe!

  SECTION("an empty or invalid file name returns and empty vector ")
  {
    REQUIRE_THAT(AoCLib::vectorise_char_data(""), IsEmpty());
    REQUIRE_THAT(AoCLib::vectorise_char_data(tmp_file.str()), Catch::Matchers::IsEmpty());
  }

  SECTION("a file with no data returns a single empty vector")
  {
    const std::ofstream test_file{ tmp_file.str() };
    if (!test_file) {
      std::cerr << "Test file " << tmp_file.str() << "could not be opened for writing\n";
    }

    const AoCLib::char_data no_data_vector{ {} };
    REQUIRE_THAT(
      AoCLib::vectorise_char_data(tmp_file.str()), Catch::Matchers::Equals(no_data_vector));
  }

  SECTION(
    "a file with a single line of data returns a single vector containing the same no of vectors "
    "as characters in the line.")
  {
    std::ofstream test_file{ tmp_file.str() };
    const std::string test_data{ "ABC" };

    if (!test_file) {
      std::cerr << "Test file " << tmp_file.str() << "could not be opened for writing\n";
    }

    test_file << test_data << std::flush;
    const AoCLib::char_data data_vector{ { 'A', 'B', 'C' } };
    REQUIRE_THAT(AoCLib::vectorise_char_data(tmp_file.str()), Catch::Matchers::Equals(data_vector));
  }

  SECTION("empty lines are returned as vectors with empty strings")
  {

    std::ofstream test_file{ tmp_file.str() };
    std::string test_data{ "" };

    if (!test_file) {
      std::cerr << "Test file " << tmp_file.str() << "could not be opened for writing\n";
    }

    test_file << test_data << std::flush;
    AoCLib::char_data data_vector{ {} };
    CHECK_THAT(AoCLib::vectorise_char_data(tmp_file.str()), Catch::Matchers::Equals(data_vector));

    test_data.append(" ");
    test_file << test_data << std::flush;
    data_vector.clear();
    data_vector.push_back({ ' ' });
    CHECK_THAT(AoCLib::vectorise_char_data(tmp_file.str()), Catch::Matchers::Equals(data_vector));

    test_data.clear();
    test_data.append("\nABC\n ");
    test_file << test_data << std::flush;
    data_vector.push_back({ 'A', 'B', 'C' });
    data_vector.push_back({ ' ' });
    CHECK_THAT(AoCLib::vectorise_char_data(tmp_file.str()), Catch::Matchers::Equals(data_vector));

    test_data.clear();
    test_data.append("\nDEF,   IJK,   LMN");
    test_file << test_data << std::flush;
    data_vector.push_back(
      { 'D', 'E', 'F', ',', ' ', ' ', ' ', 'I', 'J', 'K', ',', ' ', ' ', ' ', 'L', 'M', 'N' });

    CHECK_THAT(AoCLib::vectorise_char_data(tmp_file.str()), Catch::Matchers::Equals(data_vector));
  }

  // clean up after each test
  std::filesystem::path temp_file_path = tmp_file.str();
  if (std::filesystem::exists(temp_file_path)) { std::filesystem::remove(temp_file_path); }
}

TEST_CASE(" verify splitting string into chunks")
{
  std::string test_string{ "Now is the time for all good men to come to the aid of the party" };
  std::vector<std::string> expected
  {
    "Now is", " the t", "ime fo", "r all ", "good m", "en to ", "come t", "o the ", "aid of",
      " the p", "arty"
  };

  CHECK_THAT(AoCLib::split_string_into_chunks(test_string, 6), Catch::Matchers::Equals(expected));
}