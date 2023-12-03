#include "2023_day03.hpp"

Schematic inflate_schematic(const Schematic &engine)
{
  if (engine.empty()) { return Schematic{}; }

  const size_t engine_rows{ engine.size() };
  const size_t engine_cols{ engine[0].size() };

  const size_t inflated_rows{ engine_rows + 2 };
  const size_t inflated_cols{ engine_cols + 2 };

  Schematic search_schematic(inflated_rows, std::vector<char>(inflated_cols, '.'));

  for (size_t engine_row{}; engine_row < engine_rows; ++engine_row) {
    for (size_t engine_col{ 0 }; engine_col < engine_cols; ++engine_col) {
      search_schematic[engine_row + 1][engine_col + 1] = engine[engine_row][engine_col];
    }
  }

  return search_schematic;
}

// NOLINTBEGIN(readability-function-cognitive-complexity)
int calculate_partno_sum(Schematic &bounded_schematic, PossibleGears &gear_map)
{
  if (bounded_schematic.empty()) { return 0; }

  constexpr int decade_multiplier{ 10 };
  int part_no_sum{};

  for (size_t row_no{ 0 }; auto &schematic_row : bounded_schematic) {
    for (size_t col_no{ 0 }; auto &item : schematic_row) {
      if (isdigit(item) == 0) {
        ++col_no;
        continue;
      }
      int item_val = item - '0';
      item = '.';
      size_t next_digit_position{ col_no + 1 };
      auto next_item{ bounded_schematic[row_no][next_digit_position] };
      while (isdigit(next_item) != 0) {
        item_val = item_val * decade_multiplier + (next_item - '0');
        bounded_schematic[row_no][next_digit_position] = '.';
        ++next_digit_position;
        next_item = bounded_schematic[row_no][next_digit_position];
      }
      if (check_box_for_symbol(
            bounded_schematic, row_no, col_no - 1, next_digit_position, gear_map, item_val)) {
        part_no_sum += item_val;
      }
      ++col_no;
    }
    ++row_no;
  }

  return part_no_sum;
}
// NOLINTEND(readability-function-cognitive-complexity)

// NOLINTBEGIN(bugprone-easily-swappable-parameters)
bool check_box_for_symbol(const Schematic &schematic,
  size_t current_row,
  size_t start_col,
  size_t end_col,
  PossibleGears &gear_map,
  int found_value)
{
  bool is_item{ false };
  for (size_t check_row{ current_row - 1 }; check_row < current_row + 2; ++check_row) {
    for (size_t check_col{ start_col }; check_col <= end_col; ++check_col) {
      const auto item{ schematic[check_row][check_col] };
      if (item != '.' && isdigit(item) != 1) { is_item = true; }
      if (item == '*') {
        const auto gear_map_iterator = gear_map.find({ check_row, check_col });
        if (gear_map_iterator == gear_map.end()) {
          gear_map.emplace(
            std::make_pair(Location{ check_row, check_col }, PossibleGear{ 1, found_value }));
        } else {
            auto [count, ratio] = gear_map[Location{check_row, check_col}];
            count++;
            ratio *= found_value;
            gear_map[Location{check_row, check_col}].first++;
            gear_map[Location{check_row, check_col}].second *= found_value; 
        }
      }
    }
  }
  return is_item;
}
// NOLINTEND(bugprone-easily-swappable-parameters)