#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include <iostream>

#include <2023_day19.hpp>

// start with a test case that does nothing but fail.

TEST_CASE(" 2023 day19 testing not started", "[day19]")
{
  std::string data_file = CURRENT_LIST_DIR;
  data_file += "/test.txt";

  const AoCLib::line_data puzzle_data{ AoCLib::vectorise_line_data(data_file) };

  SECTION("check building the parts")
  {
    auto parts(create_parts_inventory(puzzle_data));

    CHECK(parts.size() == 5);
    CHECK(parts[1].aero == 2067);
    CHECK(parts[2].shiny == 2244);
    CHECK(parts[0].cool == 787);
    CHECK(parts[4].musical == 1623);
  }

  SECTION("check building of workflows")
  {
    auto workflows{ create_workflows(puzzle_data) };

    CHECK(workflows.size() == 11);
  }

  SECTION("check building the indexes and returning the correct start next")
  {
    auto workflows(create_workflows(puzzle_data));

    auto start{ build_indexes(workflows) };

    CHECK(start == 7);
    CHECK(workflows[0].second.front().next == 5);
  }

  SECTION("check the do operation part of the machine")
  {
    auto parts{ create_parts_inventory(puzzle_data) };
    auto workflows(create_workflows(puzzle_data));
    auto start{ build_indexes(workflows) };

    auto &part{ parts.front() };

    Workflow workflow(workflows[start]);
    bool finished{ false };

    while (!finished) {
      for (const auto &operation : workflow.second) {
        PassFail pass_fail{ operation.do_rule(part) };
        if (std::get<0>(pass_fail) == false) {
          if (std::get<1>(pass_fail) == std::numeric_limits<size_t>::max()) {
            part.accepted = (std::get<2>(pass_fail) == "A");
            finished = true;
            break;
          }
          workflow = workflows[std::get<1>(pass_fail)];
          break;
        }
      }
    }

    CHECK(parts[0].accepted == true);
  }

  SECTION("check do_workflow")
  {
    auto parts{ create_parts_inventory(puzzle_data) };
    auto workflows(create_workflows(puzzle_data));
    auto start{ build_indexes(workflows) };

    do_workflows(workflows, parts[2], start);
    do_workflows(workflows, parts[3], start);

    CHECK(parts[2].accepted == true);
    CHECK(parts[3].accepted == false);
  }

  SECTION("check calculation of accepted parts")
  {
    auto parts{ create_parts_inventory(puzzle_data) };
    auto workflows(create_workflows(puzzle_data));
    auto start{ build_indexes(workflows) };

    for (auto &part : parts) { do_workflows(workflows, part, start); }

    CHECK(accepted_ratings_total(parts) == 19114);
  }

  SECTION("check generatiting accepted ratings")
  {
    auto workflows(create_workflows(puzzle_data));
    auto start{ build_indexes(workflows) };

    auto accepted_ratings{ get_accepted_ratings(workflows, start) };

    int64_t total{};
    for(const auto &ratings : accepted_ratings) {
      std::cout << "(" << ratings.x_left.first << ", " << ratings.x_left.second << ") , ";
      std::cout << "(" << ratings.m_left.first << ", " << ratings.m_left.second << ") , ";
      std::cout << "(" << ratings.a_left.first << ", " << ratings.a_left.second << ") , ";
      std::cout << "(" << ratings.s_left.first << ", " << ratings.s_left.second << ")\n";
    }

    for (const auto &result : accepted_ratings) {
      int64_t result_total{ 1 };
      result_total *= (result.x_left.second - result.x_left.first + 1);
      result_total *= (result.m_left.second - result.m_left.first + 1);
      result_total *= (result.a_left.second - result.a_left.first + 1);
      result_total *= (result.s_left.second - result.s_left.first + 1);
      total += result_total;
    }
    
    CHECK(total == 167409079868000);
  }
}