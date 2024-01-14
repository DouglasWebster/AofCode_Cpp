#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include <iostream>

#include <2023_day17.hpp>

// start with a test case that does nothing but fail.

TEST_CASE(" 2023 day17 testing", "[day17]")
{
  std::string data_file = CURRENT_LIST_DIR;
  data_file += "/test.txt";

  const AoCLib::char_data puzzle_test_data{ AoCLib::vectorise_char_data(data_file) };

  SECTION("creating the edges vector") {
    Edges edges(create_edges(puzzle_test_data));

    const size_t edges_size{ puzzle_test_data.size() * puzzle_test_data[0].size() * 4 - 4 * puzzle_test_data.size()}  ;

    CHECK(edges.size() == edges_size);
    CHECK(edges[0].dest == 13);
    CHECK(edges[0].heat_loss == 3);  
  }

  SECTION("check creation of the City") {
    Edges edges{create_edges(puzzle_test_data)};
    const size_t nodes{puzzle_test_data.size() * puzzle_test_data[0].size()};

    City city(edges, nodes);

    CHECK(city.adj_list.size() == nodes);
    CHECK(city.adj_list[0].size() == 2);
    CHECK(city.adj_list[1].size() == 3);
    CHECK(city.adj_list[14].size() == 4);
  }
}
