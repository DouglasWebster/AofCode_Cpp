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

using Excavation = std::vector<std::vector<char>>;

// The extent left and right of up and down from the start cube
using Extent = std::pair<size_t, size_t>;

// the Up-Down and Left-Right extents
using Extents = std::pair<Extent, Extent>;

DigPlan create_plan(const AoCLib::line_data &puzzle_data);

Extents calc_dig_extents(const DigPlan &dig_plan);

Excavation dig_ditches(const DigPlan &dig_plan, const Extents &extents);

void draw_excavation(const Excavation &excavation);


void create_lagoon(Excavation &excavation);

int count_lagoon_size(const Excavation &excavation);

void print_excavation(const Excavation &excavation, const std::string &file_name);

void mark_external(Excavation &excavation);

using CoOrdinate = std::pair<double, double>;
using Vertices = std::vector<CoOrdinate>;


using DigiPlanInfo = std::pair<double, Vertices>;

DigiPlanInfo create_vertices(const DigPlan &dig_plan);

double shoelace_area(const Vertices &vertices);



