#pragma once

#include <string>

#include <AofCode_Cpp/aoc_library.hpp>

namespace AofCode_Cpp::cmake {
    inline constexpr std::string_view campaign_year = "2023";
    inline constexpr std::string_view campaign_day = "day18";
} //namespace AofCode::cmake

enum class Direction {
    R,
    L,
    U,
    D
};

struct Trench {
    Direction direction;
    size_t length;
    std::string hex_code;
};

using DigPlan = std::vector<Trench>;

DigPlan create_plan(const AoCLib::line_data &puzzle_data);
DigPlan decode_hex(const AoCLib::line_data &puzzle_data);

using CoOrdinate = std::pair<double, double>;
using Vertices = std::vector<CoOrdinate>;
using DigiPlanInfo = std::pair<double, Vertices>;

DigiPlanInfo create_vertices(const DigPlan &dig_plan);

double shoelace_area(const Vertices &vertices);




