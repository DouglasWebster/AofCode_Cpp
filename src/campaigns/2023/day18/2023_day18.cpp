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
