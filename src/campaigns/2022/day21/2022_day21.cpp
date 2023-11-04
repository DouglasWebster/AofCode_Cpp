#include "2022_day21.hpp"
#include <map>

auto create_data_vector(const AoCLib::str_data &data) -> MonkeyData
{

  constexpr int name_position{ 0 };
  constexpr int name_lengths{ 4 };
  constexpr int val_position{ 6 };
  constexpr int lh_name_position{ 6 };
  constexpr int operand_position{ 11 };
  constexpr int rh_name_position{ 13 };
  constexpr int value_max_position{ 10 };

  if (data.empty()) { return { MonkeyData{} }; }

  std::vector<MonkeyInfo> monkey_calculation;

  for (const auto &monkey : data) {
    const auto &info{ monkey[0] };

    MonkeyInfo monkey_data;
    monkey_data.name = info.substr(name_position, name_lengths);
    if (info.length() < value_max_position) {
      monkey_data.value = stoi(info.substr(val_position));
    } else {
      monkey_data.lh_name = info.substr(lh_name_position, name_lengths);
      auto operand = info[operand_position];
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
      monkey_data.rh_name = info.substr(rh_name_position);
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

// NOLINTBEGIN(misc-no-recursion)
auto calculate_part_1(const MonkeyData &monkey_data, size_t start_index) -> int
{
  if (monkey_data.empty()) { return 0; }

 const MonkeyInfo &monkey{ monkey_data[start_index] };

  switch (monkey.operand) {
  case Operand::No_Op:
    return monkey.value;
    break;
  case Operand::Add:
    return calculate_part_1(monkey_data, monkey.lh_vector_index)
           + calculate_part_1(monkey_data, monkey.rh_vector_index);
    break;
  case Operand::Subtract:
    return calculate_part_1(monkey_data, monkey.lh_vector_index)
           - calculate_part_1(monkey_data, monkey.rh_vector_index);
    break;
  case Operand::Multiply:
    return calculate_part_1(monkey_data, monkey.lh_vector_index)
           * calculate_part_1(monkey_data, monkey.rh_vector_index);
    break;
  case Operand::Divide:
    return calculate_part_1(monkey_data, monkey.lh_vector_index)
           / calculate_part_1(monkey_data, monkey.rh_vector_index);  // NOLINT
    break;

  default:
    break;
  };

  return 0;
}
// NOLINTEND(misc-no-recursion)
