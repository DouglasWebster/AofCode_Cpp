#include "2023_day13.hpp"
#include <algorithm>
#include <string_view>

Patterns get_patterns(const AoCLib::str_data &puzzle_data)
{
  Patterns patterns{};

  if (puzzle_data.empty()) { return patterns; }

  Pattern pattern{};
  for (const auto &data : puzzle_data) {
    if (data.empty()) {
      patterns.push_back(pattern);
      pattern.clear();
      continue;
    }
    pattern.push_back(data[0]);
  }
  patterns.push_back(pattern);

  return patterns;
}

int count_mismatches(const Mirrors &mirrors_1, const Mirrors &mirrors_2)
{
  int mismatches{};

  for (size_t index{}; index < mirrors_1.size(); ++index) {
    if (mirrors_1[index] != mirrors_2[index]) { ++mismatches; }
  }

  return mismatches;
}

Pattern transpose_pattern(const Pattern &pattern)
{
  if (pattern.empty()) { return Pattern{}; }

  const size_t t_rows = pattern[0].size();
  const size_t t_cols = pattern.size();

  Pattern transposed{ t_rows, std::string(t_cols, '.') };

  for (size_t row{}; row < t_cols; ++row) {
    for (size_t col{}; col < t_rows; ++col) { transposed[col][row] = pattern[row][col]; }
  }

  return transposed;
}


size_t is_horizontal_reflection(const Pattern &pattern)
{
  if (pattern.empty()) { return 0; }

  const size_t pattern_size{ pattern.size() };

  for (size_t lines{ 1 }; lines < pattern_size; ++lines) {
    std::string first{};
    std::string second{};
    for (size_t line_1{ lines }, line_2{ lines }; line_1 > 0 && line_2 < pattern_size;
         --line_1, ++line_2) {
      first += pattern[line_1 - 1];
      second += pattern[line_2];
      if (first != second) { break; }
    }
    if (first == second) { return lines; }
  }

  return 0;
}

size_t is_vertical_reflection(const Pattern &pattern)
{
  if (pattern.empty()) { return 0; }

  return is_horizontal_reflection(transpose_pattern(pattern));
}

size_t is_repaired_horizontal_reflection(const Pattern &pattern)
{
  if (pattern.empty()) { return 0; }

  const size_t pattern_size{ pattern.size() };

//   size_t reflexion_line{};
//   int no_repaired{};

  for (size_t lines{ 1 }; lines < pattern_size; ++lines) {
    std::string first{};
    std::string second{};
    for (size_t line_1{ lines }, line_2{ lines }; line_1 > 0 && line_2 < pattern_size;
         --line_1, ++line_2) {
      first += pattern[line_1 - 1];
      second += pattern[line_2];
      if (first != second) {
        // if (count_mismatches(first, second) != 1) { break; }
        // reflexion_line = lines;
        // ++no_repaired;
        // break;
        if (count_mismatches(first, second) == 1) { return lines; }
      }
    }
  }

  //   return no_repaired == 1 ? reflexion_line : 0;
  return 0;
}

size_t is_repaired_vertical_reflection(const Pattern &pattern)
{
  if (pattern.empty()) { return 0; }

  return is_repaired_horizontal_reflection(transpose_pattern(pattern));
}

Repair do_repair(const Pattern &pattern)
{
  if (pattern.empty()) { return Repair{ Axis::Horizontal, 0 }; }

  const size_t orignal_h_line = is_horizontal_reflection(pattern);
  const size_t new_h_line{ is_repaired_horizontal_reflection(pattern) };
  const size_t orignal_v_line = is_vertical_reflection(pattern);
  const size_t new_v_line = is_repaired_vertical_reflection(pattern);


  if (orignal_h_line != new_h_line && orignal_v_line != new_v_line) {
    std::cout << "Both reflection ines have been changed\n";
    return Repair{ Axis::Vertical, 0 };
  }

  if (new_h_line != orignal_h_line) { return Repair{ Axis::Horizontal, new_h_line }; }
  if (new_v_line != orignal_v_line) { return Repair{ Axis::Vertical, new_v_line }; }

  return Repair{ Axis::Vertical, 0 };
}

std::pair<size_t, size_t> do_all_repair(const Pattern &pattern)
{
  if (pattern.empty()) { return { 0, 0 }; }

  const size_t new_vertical{ is_repaired_vertical_reflection(pattern) };
  const size_t new_horizontal{ is_repaired_horizontal_reflection(pattern) };

  return { new_horizontal, new_vertical };
}
