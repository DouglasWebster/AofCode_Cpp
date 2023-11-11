#include <iostream>

#include "2022_day21.hpp"

int main()
{

  std::string data_file = CURRENT_LIST_DIR;
  data_file += "/input.txt";

  const AoCLib::str_data raw_vector{ AoCLib::vectorise_string_data(data_file) };

  MonkeyData monkey_data{ create_data_vector(raw_vector) };
  auto [root_index, humn_index] = build_tree_links(monkey_data);

  std::cout << "root is at: " << root_index << ", humn is at: " << humn_index << '\n';

  const int64_t part_1_solution{ calculate_totals(monkey_data, root_index) };

  const AncestorOperands ancestors{ get_ancestors("humn", monkey_data) };
  const int64_t target{ calculate_sum_to_balance(monkey_data) };

  const PartialSums partial_sums{ calculate_partial_sums(monkey_data, ancestors) };

  auto part_2_solution{ calc_humn_value(partial_sums, target) };

  std::cout << "Advent of Code " << AofCode_Cpp::cmake::campaign_year << " "
            << AofCode_Cpp::cmake::campaign_day << '\n';
  std::cout << "Part 1 solution: " << part_1_solution << '\n';
  std::cout << "Part 2 solution: " << part_2_solution << '\n';

  const auto lhs_index = monkey_data[root_index].lh_vector_index;
  const auto rhs_index = monkey_data[root_index].rh_vector_index;

  auto lhs_sum{ calculate_totals(monkey_data, lhs_index) };
  const auto rhs_sum{ calculate_totals(monkey_data, rhs_index) };
  auto error = lhs_sum - rhs_sum;
  std::cout << "LHS = " << lhs_sum << " and RHS = " << rhs_sum << '\n';
  std::cout << "error : " << error << ", humn operand: " << monkey_data[humn_index].operand << "\n";

  int iteration{ 0 };
  constexpr auto max_iterations{ 10000 };
  // constexpr int64_t correction{ 3757272361482 };

  const int64_t correction{ part_2_solution };
  const int64_t offset{ part_2_solution / 10 };
  monkey_data[humn_index].operand = correction;
  while (error > 0 && iteration < max_iterations) {
    monkey_data[humn_index].operand -= offset;
    lhs_sum = calculate_totals(monkey_data, lhs_index);
    error = lhs_sum - rhs_sum;
    ++iteration;
    std::cout << "error: " << error << ", humn operand: " << monkey_data[humn_index].operand
              << "\n";
  }


  return 0;
}
