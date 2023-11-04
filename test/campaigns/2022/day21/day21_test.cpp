#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include <iostream>

#include <2022_day21.hpp>

// start with a test case that does nothing but fail.

TEST_CASE(" 2022 day21 testing not started", "[day21]")
{
  AoCLib::str_data test_data{ { "root: pppw + sjmn" },
    { "dbpl: 5" },
    { "cczh: sllz + lgvd" },
    { "zczc: 2" },
    { "ptdq: humn - dvpt" },
    { "dvpt: 3" },
    { "lfqf: 4" },
    { "humn: 5" },
    { "ljgn: 2" },
    { "sjmn: drzm * dbpl" },
    { "sllz: 4" },
    { "pppw: cczh / lfqf" },
    { "lgvd: ljgn * ptdq" },
    { "drzm: hmdt - zczc" },
    { "hmdt: 32" } };

    SECTION( " check creation of MonkeyInfo") {
        const auto result{create_data_vector(test_data)};

        CHECK(result.front().name == "root" );
        CHECK(result.front().value == 0);
        CHECK(result[1].value == 5);
        CHECK(result[5].lh_name == "");
        CHECK(result[13].rh_name == "zczc");
        CHECK(result[11].operand == Operand::Divide);
        CHECK(result.back().name == "hmdt");
    }

    SECTION("check creation of tree links") {
      auto results(create_data_vector(test_data));
      build_tree_links(results);

      CHECK(results.front().lh_vector_index == 11);
      CHECK(results[11].rh_vector_index == 6);
      CHECK(results[6].lh_vector_index == 0);
      CHECK(results[11].lh_vector_index == 2);
    }

    SECTION(" check test result") {

      auto results(create_data_vector(test_data));
      build_tree_links(results);
      MonkeyData no_data{};

      CHECK(calculate_part_1(no_data) == 0);
      CHECK(calculate_part_1(results) == 152);

    }

}
