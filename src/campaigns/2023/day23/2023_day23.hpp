#pragma once

#include <numeric>
#include <string>
#include <map>

#include <AofCode_Cpp/aoc_library.hpp>

namespace AofCode_Cpp::cmake {
inline constexpr std::string_view campaign_year = "2023";
inline constexpr std::string_view campaign_day = "day23";
}// namespace AofCode_Cpp::cmake

constexpr size_t max_location{ std::numeric_limits<size_t>::max() };
enum Heading { North = 0, South, East, West, Nowhere };


struct Location
{
  size_t index{ max_location };
  size_t North{ max_location };
  size_t South{ max_location };
  size_t East{ max_location };
  size_t West{ max_location };
  int exits{};

  std::vector<size_t> to_visit() const
  {
    std::vector<size_t> next{};
    next.reserve(4);
    if (North != max_location) { next.push_back(North); }
    if (South != max_location) { next.push_back(South); }
    if (East != max_location) { next.push_back(East); }
    if (West != max_location) { next.push_back(West); }

    return next;
  }
};

using TrailMap = std::vector<Location>;

/**
 * @brief build a graph of the trails.
 *
 * @param puzzle_data
 * @param passable if true then the path can go up slopes.
 * @return TrailMap
 *
 * Note > prevents moving west, < prevents moving east, ^ prevents moving south
 * and v prevents moving north.
 */
TrailMap build_trails(const AoCLib::char_data data);


using TrailEdge = std::pair<size_t, int>;
using TrailEdges = std::vector<TrailEdge>;
using TrailGraph = std::map<size_t, TrailEdges>;

/**
 * @brief Build the DAG for the trail.
 *
 * @param trail_map the vector of movements allowed on the trail
 * @return TrailGraph
 */
TrailGraph build_trail_graph(const TrailMap &trail_map);

/**
 * @brief create a vector ordered topologically for the trail graph supplied
 * 
 * @param trail_graph 
 * @return std::vector<size_t> 
 */
std::vector<size_t> topological_sort(const TrailGraph &trail_graph);

/**
 * @brief given a DAG and a topological sort return the longest path
 * 
 * @param trail_graph A weighted DAG
 * @param order the topological sort of the supplied DAG
 * @return int the longest path from the first to last nodes.
 */
int longest_path(const TrailGraph &trail_graph, const std::vector<size_t> &order );
