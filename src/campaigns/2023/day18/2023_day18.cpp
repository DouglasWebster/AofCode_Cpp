#include "2023_day18.hpp"
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <stack>

DigPlan create_plan(const AoCLib::line_data &puzzle_data)
{

  if (puzzle_data.empty()) { return DigPlan{}; }
  DigPlan dig_plan{};
  for (const auto &line : puzzle_data) {
    auto data{ AoCLib::split_string_at_delimter(line, ' ') };
    Trench trench{};
    const char facing{ data[0][0] };
    switch (facing) {
    case 'U':
      trench.direction = Direction::U;
      break;
    case 'D':
      trench.direction = Direction::D;
      break;
    case 'L':
      trench.direction = Direction::L;
      break;
    case 'R':
      trench.direction = Direction::R;
      break;
    default:
      break;
    }
    trench.length = std::stoul(data[1]);
    trench.hex_code = data[2];
    dig_plan.emplace_back(trench);
  }


  return dig_plan;
}

Extents calc_dig_extents(const DigPlan &dig_plan)
{
  if (dig_plan.empty()) { return Extents{}; }

  int min_UD{};
  int max_UD{};
  int max_LR{};
  int min_LR{};

  int current_UD{};
  int current_LR{};

  for (const auto &trench : dig_plan) {
    auto length = static_cast<int>(trench.length);
    switch (trench.direction) {
    case Direction::U:
      current_UD += length;
      if (current_UD > max_UD) { max_UD = current_UD; }
      break;
    case Direction::D:
      current_UD -= length;
      if (current_UD < min_UD) { min_UD = current_UD; }
      break;
    case Direction::L:
      current_LR -= length;
      if (current_LR < min_LR) { min_LR = current_LR; }
      break;
    case Direction::R:
      current_LR += length;
      if (current_LR > max_LR) { max_LR = current_LR; }
      break;
    }
  }

  const auto extent_left = static_cast<size_t>(abs(min_LR));
  const auto extent_right = static_cast<size_t>(abs(max_LR));
  const auto extent_up = static_cast<size_t>(abs(max_UD));
  const auto extent_down = static_cast<size_t>(abs(min_UD));


  return { { extent_up, extent_down }, { extent_left, extent_right } };
}

Excavation dig_ditches(const DigPlan &dig_plan, const Extents &extents)
{
  if (dig_plan.empty()) { return Excavation{}; }

  // Don't forget to account for the zero row, column.
  const size_t rows{ extents.first.first + extents.first.second + 3 };
  const size_t cols{ extents.second.first + extents.second.second + 3 };
  size_t start_row{ extents.first.first + 1 };
  size_t start_col{ extents.second.first + 1 };

  Excavation excavation(rows, std::vector<char>(cols, '.'));

  for (const auto &trench : dig_plan) {
    const Direction direction{ trench.direction };
    const size_t length{ trench.length };
    switch (direction) {
    case Direction::U:
      for (size_t hole{}; hole < length; ++hole) {
        excavation[start_row][start_col] = '#';
        --start_row;
      }
      break;
    case Direction::D:
      for (size_t hole{}; hole < length; ++hole) {
        excavation[start_row][start_col] = '#';
        ++start_row;
      }
      break;
    case Direction::L:
      for (size_t hole{}; hole < length; ++hole) {
        excavation[start_row][start_col] = '#';
        --start_col;
      }
      break;
    case Direction::R:
      for (size_t hole{}; hole < length; ++hole) {
        excavation[start_row][start_col] = '#';
        ++start_col;
      }
      break;
    }
  }

  return excavation;
}

void draw_excavation(const Excavation &excavation)
{
  for (const auto &row : excavation) {
    for (const auto &hole : row) { std::cout << hole; }
    std::cout << '\n';
  }
  std::cout << '\n';
}

void print_excavation(const Excavation &excavation, const std::string &file_name)
{
  std::string data_file = CURRENT_LIST_DIR;
  data_file += "/";
  data_file += file_name;

  std::ofstream lagoon_dump;
  lagoon_dump.open(data_file, std::ofstream::out | std::ofstream::trunc);

  for (const auto &row : excavation) {
    for (const auto &hole : row) { lagoon_dump << hole; }
    lagoon_dump << '\n';
  }
  lagoon_dump.close();
}

bool is_valid(const Excavation &excavation,
  std::pair<size_t, size_t> position,
  size_t row_end,
  size_t col_end)// NOLINT
{
  const auto min_limit = std::numeric_limits<size_t>::max();
  auto [row, col] = position;
  if (row == min_limit || row >= row_end || col == min_limit || col >= col_end
      || excavation[row][col] != '.') {
    return false;// NOLINT
  }
  return true;
}

void mark_external(Excavation &excavation)
{
  using Position = std::pair<size_t, size_t>;
  std::stack<Position> to_check{};

  const size_t row_end{ excavation.size() };
  const size_t col_end{ excavation[0].size() };

  to_check.emplace(0, 0);

  while (!to_check.empty()) {
    const Position position{ to_check.top() };
    to_check.pop();

    const auto row{ position.first };
    const auto col{ position.second };

    // Check if the adjacent
    // pixels are valid
    if (is_valid(excavation, Position(row + 1, col), row_end, col_end)) {
      // Color with newC
      // if valid and enqueue
      excavation[row + 1][col] = 'X';
      to_check.emplace(row + 1, col);
    }

    if (is_valid(excavation, Position(row - 1, col), row_end, col_end)) {
      // Color with newC
      // if valid and enqueue
      excavation[row - 1][col] = 'X';
      to_check.emplace(row - 1, col);
    }
    if (is_valid(excavation, Position(row, col + 1), row_end, col_end)) {
      // Color with newC
      // if valid and enqueue
      excavation[row][col + 1] = 'X';
      to_check.emplace(row, col + 1);
    }
    if (is_valid(excavation, Position(row, col - 1), row_end, col_end)) {
      // Color with newC
      // if valid and enqueue
      excavation[row][col - 1] = 'X';
      to_check.emplace(row, col - 1);
    }
  }
}


DigiPlanInfo create_vertices(const DigPlan &dig_plan)
{
  if (dig_plan.empty()) { return DigiPlanInfo{}; }

  CoOrdinate next_coord{ 0.0, 0.0 };
  Vertices vertices{}; // next_coord };
  double total_length{};

  for (const auto &trench : dig_plan) {
    const Direction direction{ trench.direction };

    auto length{static_cast<double>(trench.length)};

    total_length += length;
    switch (direction) {
    case Direction::U:
      next_coord.second += length;
      break;
    case Direction::D:
      next_coord.second -= length;
      break;
    case Direction::L:
      next_coord.first -= length;
      break;
    case Direction::R:
      next_coord.first += length;
      break;
    }
    vertices.emplace_back(next_coord);
  }
  return {total_length, vertices};
}

double shoelace_area(const Vertices &vertices)
{
  double area{ 0.0 };
  const auto last_vertex{ vertices.size() };

  for (size_t index{}; index < last_vertex; ++index) {
    const size_t previous_vertex{ (index + 1) % last_vertex };
    area += (vertices[index].first * vertices[previous_vertex].second)
            - (vertices[previous_vertex].first * vertices[index].second);
  }

  return std::abs(area) / 2.0;// NOLINT
}

void create_lagoon(Excavation &excavation)
{
  for (size_t row_index{}; row_index < excavation.size(); ++row_index) {
    mark_external(excavation);
    for (auto &row : excavation) {
      for (auto &location : row) {
        if (location == '.') { location = '#'; }
        if (location == 'X') { location = '.'; }
      }
    }
  }
}


int count_lagoon_size(const Excavation &excavation)
{
  int total_size{};

  for (const auto &row : excavation) {
    for (const auto location : row) {
      if (location == '#') { ++total_size; }
    }
  }
  return total_size;
}
