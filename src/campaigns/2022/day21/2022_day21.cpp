#include "2022_day21.hpp"
#include <map>

auto create_data_vector(const AoCLib::str_data &data) -> MonkeyData
{

  constexpr int name_position{ 0 };
  constexpr int name_lengths{ 4 };

  if (data.empty()) { return { MonkeyData{} }; }

  std::vector<MonkeyInfo> monkey_calculation;

  for (const auto &monkey : data) {

    MonkeyInfo monkey_data;

    monkey_data.name = monkey[0].substr(name_position, name_lengths);
    if (monkey.size() == 2) {
      monkey_data.value = stoi(monkey[1]);
    } else {
      monkey_data.lh_name = monkey[1];
      monkey_data.rh_name = monkey[3];

      auto operand = monkey[2][0];
      switch (operand) {
      case '*':
        monkey_data.operand = Operand::Multiply;
        break;
      case '/':
        monkey_data.operand = Operand::Divide;
        break;
      case '+':
        monkey_data.operand = Operand::Add;
        break;
      case '-':
        monkey_data.operand = Operand::Subtract;
        break;
      default:
        break;
      }
    }

    monkey_calculation.push_back(monkey_data);
  }

  return monkey_calculation;
}

void build_tree_links(MonkeyData &monkey_data)
{
  std::map<std::string, size_t> monkey_indexes;

  for (size_t index{ 0 }; const auto &monkey : monkey_data) {
    monkey_indexes.insert({ monkey.name, index });
    ++index;
  }

  for (auto &monkey : monkey_data) {
    if (monkey.operand != Operand::No_Op) {
      monkey.lh_vector_index = monkey_indexes[monkey.lh_name];// cppcheck-suppress unreadVariable
      monkey.rh_vector_index = monkey_indexes[monkey.rh_name];// cppcheck-suppress unreadVariable
    }
  }
}

auto get_root_index(const MonkeyData &monkey_data) -> size_t
{
  for (size_t index{ 0 }; const auto &monkey : monkey_data) {
    if (monkey.name == "root") { return index; }
    ++index;
  }

  return 0;
}

// NOLINTBEGIN(misc-no-recursion)
auto calculate_totals(const MonkeyData &monkey_data, size_t start_index) -> int64_t
{
  if (monkey_data.empty()) { return 0; }

  const MonkeyInfo &monkey{ monkey_data[start_index] };

  int64_t lh_sum{ 0 };
  int64_t rh_sum{ 0 };
  int64_t total{ 0 };
  switch (monkey.operand) {

  case Operand::No_Op:
#ifdef CATCH2_ACTIVE
    std::cout << monkey.name << " has value " << monkey.value << '\n';
#endif
    total = monkey.value;
    break;

  case Operand::Add:
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

  case Operand::Subtract:
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

  case Operand::Multiply:
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

  case Operand::Divide:
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
