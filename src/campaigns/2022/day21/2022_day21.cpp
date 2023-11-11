#include "2022_day21.hpp"
#include <algorithm>
#include <map>
#include <iterator>

MonkeyData create_data_vector(const AoCLib::str_data &data)
{

  constexpr int name_position{ 0 };
  constexpr int name_lengths{ 4 };

  if (data.empty()) { return { MonkeyData{} }; }

  std::vector<MonkeyInfo> monkey_calculation;

  for (size_t location{ 0 }; const auto &monkey : data) {

    MonkeyInfo monkey_data;

    monkey_data.name = monkey[0].substr(name_position, name_lengths);
    monkey_data.location = location++;
    if (monkey.size() == 2) {
      monkey_data.operand = stoi(monkey[1]);
    } else {
      monkey_data.lh_name = monkey[1];
      monkey_data.rh_name = monkey[3];

      auto monkey_op = monkey[2][0];
      switch (monkey_op) {
      case '*':
        monkey_data.monkey_op = Operators::Multiply;
        break;
      case '/':
        monkey_data.monkey_op = Operators::Divide;
        break;
      case '+':
        monkey_data.monkey_op = Operators::Add;
        break;
      case '-':
        monkey_data.monkey_op = Operators::Subtract;
        break;
      default:
        break;
      }
    }

    monkey_calculation.push_back(monkey_data);
  }

  return monkey_calculation;
}

RootAndHumnIndex build_tree_links(MonkeyData &monkey_data)
{
  std::map<std::string, size_t> monkey_indexes;

  for (size_t index{ 0 }; const auto &monkey : monkey_data) {
    monkey_indexes.insert({ monkey.name, index });
    ++index;
  }

  for (auto &monkey : monkey_data) {
    if (monkey.monkey_op != Operators::No_Op) {
      monkey.lh_vector_index = monkey_indexes[monkey.lh_name];
      monkey_data[monkey.lh_vector_index].parent = monkey.location;
      monkey.rh_vector_index = monkey_indexes[monkey.rh_name];
      monkey_data[monkey.rh_vector_index].parent = monkey.location;
    }
  }

  return RootAndHumnIndex{monkey_indexes["root"], monkey_indexes["humn"]};
}

size_t get_root_index(const MonkeyData &monkey_data)
{
  for (size_t index{ 0 }; const auto &monkey : monkey_data) {
    if (monkey.name == "root") { return index; }
    ++index;
  }

  return 0;
}

// NOLINTBEGIN(misc-no-recursion)
int64_t calculate_totals(const MonkeyData &monkey_data, size_t start_index)
{
  if (monkey_data.empty()) { return 0; }

  const MonkeyInfo &monkey{ monkey_data[start_index] };

  int64_t lh_sum{ 0 };
  int64_t rh_sum{ 0 };
  int64_t total{ 0 };
  switch (monkey.monkey_op) {

  case Operators::No_Op:
#ifdef CATCH2_ACTIVE
    std::cout << monkey.name << " has value " << monkey.operand << '\n';
#endif
    total = monkey.operand;
    break;

  case Operators::Add:
#ifdef CATCH2_ACTIVE
    std::cout << monkey.name << ":  " << monkey.lh_name << " + " << monkey.rh_name;
#endif
    lh_sum = calculate_totals(monkey_data, monkey.lh_vector_index);
    rh_sum = calculate_totals(monkey_data, monkey.rh_vector_index);
    total = lh_sum + rh_sum;
#ifdef CATCH2_ACTIVE
    std::cout << " = " << total << '\n';
#endif
    break;

  case Operators::Subtract:
#ifdef CATCH2_ACTIVE
    std::cout << monkey.name << ":  " << monkey.lh_name << " - " << monkey.rh_name;
#endif
    lh_sum = calculate_totals(monkey_data, monkey.lh_vector_index);
    rh_sum = calculate_totals(monkey_data, monkey.rh_vector_index);
    total = lh_sum - rh_sum;
#ifdef CATCH2_ACTIVE
    std::cout << " = " << total << '\n';
#endif
    break;

  case Operators::Multiply:
#ifdef CATCH2_ACTIVE
    std::cout << monkey.name << ":  " << monkey.lh_name << " * " << monkey.rh_name;
#endif
    lh_sum = calculate_totals(monkey_data, monkey.lh_vector_index);
    rh_sum = calculate_totals(monkey_data, monkey.rh_vector_index);
    total = lh_sum * rh_sum;
#ifdef CATCH2_ACTIVE
    std::cout << " = " << total << '\n';
#endif
    break;

  case Operators::Divide:
#ifdef CATCH2_ACTIVE
    std::cout << monkey.name << ":  " << monkey.lh_name << " / " << monkey.rh_name;
#endif
    lh_sum = calculate_totals(monkey_data, monkey.lh_vector_index);
    rh_sum = calculate_totals(monkey_data, monkey.rh_vector_index);
    total = lh_sum / rh_sum;// NOLINT
#ifdef CATCH2_ACTIVE
    std::cout << " = " << total << '\n';
#endif
    break;

  default:
    break;
  };

  return total;
}
// NOLINTEND(misc-no-recursion)}

AncestorOperands get_ancestors(std::string_view monkey_name, const MonkeyData &monkey_data)
{
  AncestorOperands parent_list{};
  parent_list.reserve(monkey_data.size());
  if (monkey_data.empty() || monkey_name == "root") { return parent_list; }

  for (const auto &monkey : monkey_data) {
    if (monkey.name != monkey_name) { continue; }
    size_t parent = monkey.parent;
    Operators operand = monkey_data[parent].monkey_op;
    parent_list.emplace_back(std::make_pair(parent, operand));
    while (monkey_data[parent].name != "root") {
      parent = monkey_data[parent].parent;
      operand = monkey_data[parent].monkey_op;
      parent_list.emplace_back(std::make_pair(parent, operand));
    }
    break;
  }

  std::reverse(parent_list.begin(), parent_list.end());

  return parent_list;
}

int64_t calculate_sum_to_balance(const MonkeyData &monkey_data)
{
  AncestorOperands humn_ancestors{ get_ancestors("humn", monkey_data) };
  const auto penultimate_ancestor{ humn_ancestors[1].first };
  const auto sum_root = (monkey_data[humn_ancestors[0].first].lh_vector_index == penultimate_ancestor)
                          ? monkey_data[humn_ancestors[0].first].rh_vector_index
                          : monkey_data[humn_ancestors[0].first].lh_vector_index;
  auto sum_to_balance{ calculate_totals(monkey_data, sum_root) };
  return sum_to_balance;
}

PartialSums calculate_partial_sums(const MonkeyData &monkey_data, const AncestorOperands &ancestors)
{
  PartialSums partial_sums{};

  MonkeyInfo current_root{};
  size_t partial_sum_root{};


  for (auto ancestor_it = ancestors.begin() + 1; ancestor_it != ancestors.end() - 1;
       ++ancestor_it) {
    current_root = monkey_data[(*ancestor_it).first];
    partial_sum_root = (current_root.lh_vector_index == (*(ancestor_it + 1)).first)
                              ? current_root.rh_vector_index
                              : current_root.lh_vector_index;
    partial_sums.emplace_back(
      calculate_totals(monkey_data, partial_sum_root), current_root.monkey_op);
  }
  current_root = monkey_data[ancestors.back().first];
  partial_sum_root = (current_root.lh_name == "humn")
                            ? current_root.rh_vector_index
                            : current_root.lh_vector_index;
  partial_sums.emplace_back(calculate_totals(monkey_data, partial_sum_root), current_root.monkey_op);
  return partial_sums;
}

int64_t calc_humn_value(const PartialSums &partial_sums, int64_t target) { 
  
  for (const auto &operation : partial_sums) {
    const auto operand = operation.first;
    std::cout << "target now : " << target;

    switch (operation.second)
    {
    case Operators::Add:
      std::cout << " - " << operand << " = ";
      target -= operand;
      std:: cout << target << '\n';
      break;
    case Operators::Subtract:
      std::cout << " + " << operand << " = ";
      target += operand;
      std:: cout << target << '\n';
      break;
    case Operators::Multiply:
      std::cout << " / " << operand << " = ";
      target /= operand;
      std:: cout << target << '\n';
      break;
    case Operators::Divide:
      std::cout << " * " << operand << " = ";
      target *= operand;
      std:: cout << target << '\n';
      break;
    
    default:
      break;
    }

  }
  return target;
 }
