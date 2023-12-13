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

size_t is_horizontal_reflection(const Pattern &pattern)
{
  if (pattern.empty()) { return 0; }

  const size_t pattern_size{ pattern.size() };

  Mirrors all_mirrors{};
  for (const auto &mirrors : pattern) { all_mirrors += mirrors; }
  
  for (size_t lines{ 1 }; lines < pattern_size; ++lines) {
    std::string first{};
    std::string second{};
    for (size_t line_1{ lines }, line_2{ lines }; line_1 > 0 && line_2 < pattern_size;
         --line_1, ++line_2) {
      first += pattern[line_1 - 1];
      second += pattern[line_2];
      if(first != second) {break;}
    }
    if (first == second) { return lines; }
  }

  return 0;
}

size_t is_vertical_reflection(const Pattern &pattern) { 
  if (pattern.empty()) { return 0; }

  const size_t t_rows = pattern[0].size();
  const size_t t_cols = pattern.size();

  Pattern transposed{ t_rows, std::string(t_cols, '.') };

  for (size_t row{}; row < t_cols; ++row) {
    for (size_t col{}; col < t_rows; ++col) { transposed[col][row] = pattern[row][col]; }
  }

  return is_horizontal_reflection(transposed);
}
