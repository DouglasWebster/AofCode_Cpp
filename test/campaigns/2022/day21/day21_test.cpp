#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include <iostream>

#include <2022_day21.hpp>

// start with a test case that does nothing but fail.

TEST_CASE(" 2022 day21 testing not started", "[day21]")
{
  AoCLib::str_data test_data{ { { "root:" }, { "pppw" }, { "+" }, { "sjmn" } },
    { { "dbpl:" }, { "5" } },
    { { "cczh:" }, { "sllz" }, { "+" }, { "lgvd" } },
    { { "zczc:" }, { "2" } },
    { { "ptdq:" }, { "humn" }, { "-" }, { "dvpt" } },
    { { "dvpt:" }, { "3" } },
    { { "lfqf:" }, { "4" } },
    { { "humn:" }, { "5" } },
    { { "ljgn:" }, { "2" } },
    { { "sjmn:" }, { "drzm" }, { "*" }, { "dbpl" } },
    { { "sllz:" }, { "4" } },
    { { "pppw:" }, { "cczh" }, { "/" }, { "lfqf" } },
    { { "lgvd:" }, { "ljgn" }, { "*" }, { "ptdq" } },
    { { "drzm:" }, { "hmdt" }, { "-" }, { "zczc" } },
    { { "hmdt:" }, { "32" } } };

  SECTION(" check creation of MonkeyInfo")
  {
    const auto result{ create_data_vector(test_data) };

    CHECK(result.front().name == "root");
    CHECK(result.front().operand == 0);
    CHECK(result[1].operand == 5);
    CHECK(result[5].lh_name == "");
    CHECK(result[13].rh_name == "zczc");
    CHECK(result[11].monkey_op == Operators::Divide);
    CHECK(result.back().name == "hmdt");
  }

  SECTION("check creation of tree links")
  {
    auto results(create_data_vector(test_data));
    build_tree_links(results);

    CHECK(results.front().lh_vector_index == 11);
    CHECK(results[11].rh_vector_index == 6);
    CHECK(results[6].lh_vector_index == 0);
    CHECK(results[11].lh_vector_index == 2);
  }

  SECTION(" check part one result")
  {

    auto results(create_data_vector(test_data));
    build_tree_links(results);
    MonkeyData no_data{};

    CHECK(calculate_totals(no_data) == 0);
    CHECK(calculate_totals(results) == 152);
  }

  SECTION("check getting parent list")
  {
    auto results(create_data_vector(test_data));
    build_tree_links(results);

    CHECK(get_ancestors("root", results).empty());
    AncestorOperands ancestors{ get_ancestors("pppw", results) };
    CHECK(ancestors.size() == 1);
    CHECK(ancestors[0].first == 0);
    CHECK(ancestors[0].second == Operators::Add);

    ancestors = get_ancestors("sllz", results);
    CHECK(ancestors.size() == 3);
    CHECK(ancestors[2].first == 2);
    CHECK(ancestors[2].second == Operators::Add);
    CHECK(ancestors[1].first == 11);
    CHECK(ancestors[1].second == Operators::Divide);
    CHECK(ancestors[0].first == 0);
    CHECK(ancestors[0].second == Operators::Add);

    ancestors = get_ancestors("humn", results);
    CHECK(ancestors.size() == 5);
    CHECK(ancestors[4].first == 4);
    CHECK(ancestors[4].second == Operators::Subtract);
    CHECK(ancestors[2].first == 2);
    CHECK(ancestors[2].second == Operators::Add);
    CHECK(ancestors[0].first == 0);
    CHECK(ancestors[0].second == Operators::Add);
  }

  SECTION("check balance sum is obtained correctly")
  {
    auto results(create_data_vector(test_data));
    build_tree_links(results);

    CHECK(calculate_sum_to_balance(results) == 150);
  }

  SECTION("check partial sum is obtained correctly")
  {
    auto results(create_data_vector(test_data));
    build_tree_links(results);
    auto ancestors{ get_ancestors("humn", results) };
    auto partial_sums{ calculate_partial_sums(results, ancestors) };

    PartialSums expected{ std::make_pair(4, Operators::Divide),
      std::make_pair(4, Operators::Add),
      std::make_pair(2, Operators::Multiply),
      std::make_pair(3, Operators::Subtract) };

    CHECK_THAT(partial_sums, Catch::Matchers::Equals(expected));
  }
  
  SECTION("check the final value is obtained correctly")
  {
    auto results(create_data_vector(test_data));
    build_tree_links(results);
    const int64_t target{calculate_sum_to_balance(results)};
    auto ancestors{ get_ancestors("humn", results) };
    auto partial_sums{ calculate_partial_sums(results, ancestors) };

    CHECK(calc_humn_value(partial_sums, target) == 301);
  }
}
