#pragma once

#include <numeric>
#include <string>
#include <vector>

#include <AofCode_Cpp/aoc_library.hpp>

namespace AofCode_Cpp::cmake {
inline constexpr std::string_view campaign_year = "2023";
inline constexpr std::string_view campaign_day = "day17";
}// namespace AofCode_Cpp::cmake

enum Heading {
  North = 0,
  South,
  East,
  West,
  Nowhere
};

struct Edge
{
  size_t source, dest;
  size_t heat_loss;
  Heading heading;
};

struct Adjacency
{
  size_t dest;
  size_t heat_loss;
  Heading heading;
};

using Edges = std::vector<Edge>;
using AdjacencyList = std::vector<std::vector<Adjacency>>;

struct City
{
  AdjacencyList adj_list;

  City(const Edges &edges, size_t element_count)
  {
    adj_list.resize(element_count);
    for (const auto &edge : edges) {
      adj_list[edge.source].emplace_back(Adjacency{ edge.dest, edge.heat_loss, edge.heading });
    }
  }
};

constexpr size_t max_block{ std::numeric_limits<size_t>::max() };

/**
 * @brief Create an vector of Edge objects.  An Edge has a source and destination vertex id along
 * with the heat loss incured on entering the destination vertex and the direction from which the
 * destination is entered.
 *
 * @param data A vector of vectors of chars representing the energy loss for each city block
 * @return Edges
 * 
 */
Edges create_edges(const AoCLib::char_data &data);

/** A vector of pairs representing the shortest paths from a given starting vertex.
 * First -> the vertex,
 * Second -> the distance (weight);
 * 
 */
using ShortestPaths = std::pair<size_t, size_t>;

/**
 * @brief get the energy used moving a crucible to every vertex in the city
 *
 * @param city An adjancey list for the city blocks (vertices)
 * @return ShortestPaths
 *
 * This uses Dijkstra's algorithm with ammendments to prevent traversing more than
 * three blocks in a straight line.  The algorithm itself should prevent retracing
 * steps.
 * 
 */
ShortestPaths energy_used(const City &city, const int min_steps = 1, const int max_steps = 3);