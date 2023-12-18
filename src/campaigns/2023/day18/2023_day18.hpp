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
    Direction directection;
    size_t length;
    std::string hex_code;
};

using DigPlan = std::vector<Trench>;

DigPlan create_plan(const AoCLib::line_data &puzzle_data);