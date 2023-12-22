#pragma once

#include <string>

#include <AofCode_Cpp/aoc_library.hpp>

namespace AofCode_Cpp::cmake {
    inline constexpr std::string_view campaign_year = "2023";
    inline constexpr std::string_view campaign_day = "day10";
} //namespace AofCode::cmake

enum ConnectionType {
    Vertical = '|',
    Horizontal = '-',
    NorthEast = 'L',
    NorthWest = 'J',
    SouthWetst = '7',
    SouthEast = 'F',
    Ground = '.',
    Start = 'S'
};

enum class Connection {
    North,
    South,
    East,
    West,
    Ground,
    Start
};

enum class GroundType {
    Path,
    Pipe,
    Ground,
};

/**
 * @brief the pipe shows the connection direction N-S first then E-W
 * 
 */
using Pipe = std::pair<Connection, Connection>;
using Sketch = std::vector<std::vector<Pipe>>;
using Location = std::pair<size_t, size_t>;
using MapData = std::pair<Location, Sketch>;
using LocationTypes = std::vector<std::vector<GroundType>>;

/**
 * @brief construct a Sketch from the puzzle_data
 * 
 * @param puzzle_data a 2d vector of characters
 * @param locations a map of the ground that needs to be filled in with path locations
 * @return Sketch a 2d vector of Connections
 */
MapData build_map_data(const AoCLib::char_data & puzzle_data, LocationTypes &locations);

/**
 * @brief Set the type of ground at each location
 * 
 * @param map_data a map with the path already allocated/
 * @return LocationTypes 
 */
LocationTypes set_locations(const AoCLib::char_data & puzzle_data);

/**
 * @brief given a map of the pipes count how many steps it takes to return
 * to the start
 * 
 * @param map_data 
 * @return size_t 
 */
size_t count_steps(const MapData &map_data);

/**
 * @brief count the number of Ground locations that are inside the loop
 * 
 * @param locations a map showing the type of object at each location;
 * @return size_t t
 */
size_t count_inner_tiles(const LocationTypes &locations);

Location find_start(const AoCLib::char_data & data);
Pipe start_direction(const AoCLib::char_data & data, const Location &start_location);
AoCLib::char_data draw_map(const Location start, const Pipe &connections, const AoCLib::char_data &data);
int count_enclosed(const AoCLib::char_data &data);

void print_map(const AoCLib::char_data &data, const std::string &file_name);


