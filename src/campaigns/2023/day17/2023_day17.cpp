#include "2023_day17.hpp"
#include <cstdlib>
#include <functional>
#include <queue>
#include <limits>

Edges create_edges(const AoCLib::char_data &data)
{
  if (data.empty()) { return {}; }

  const size_t rows{ data.size() };
  const size_t cols{ data[0].size() };

  Edges edges{};
  edges.reserve(rows * cols * 4);// assume one orthogonal edge from each vetices

  // size_t row{};
  // size_t col{};

  for (size_t row{}; row < rows; ++row) {
    for (size_t col{}; col < cols; ++col) {

      const size_t north_vertex = row == 0 ? max_block : (row - 1) * cols + col;
      const size_t south_vertex = row == rows - 1 ? max_block : (row + 1) * cols + col;
      const size_t east_vertex = col == cols - 1 ? max_block : row * cols + col + 1;
      const size_t west_vertex = col == 0 ? max_block : row * cols + col - 1;

      for (int direction{}; direction < 4; ++direction) {
        Edge edge{};
        edge.source = row * cols + col;
        size_t destination{};
        Heading heading{};
        switch (direction) {
        case 0:
          destination = north_vertex;
          heading = North;
          break;
        case 1:
          destination = south_vertex;
          heading = South;
          break;
        case 2:
          destination = east_vertex;
          heading = East;
          break;
        case 3:
          destination = west_vertex;
          heading = West;
          break;
        default:
          break;
        }
        if (destination == max_block) { continue; }
        edge.dest = destination;
        edge.heading = heading;
        ldiv_t dest_link{ ldiv(static_cast<long>(destination), static_cast<long>(rows)) };
        edge.heat_loss =
          data[static_cast<size_t>(dest_link.quot)][static_cast<size_t>(dest_link.rem)] - '0';
        edges.emplace_back(edge);
      }
    }
  }
  return edges;
}

struct AdjacencyShortestPath
{
  bool operator()(const Adjacency &lhs, const Adjacency &rhs)
  {
    return lhs.heat_loss < rhs.heat_loss;
  }
};

using AdjacenyPriorityQueue = std::priority_queue<Adjacency, std::vector<Adjacency>, AdjacencyShortestPath>;

ShortestPaths energy_used(const City &city)
{
  constexpr size_t max_heat_loss{std::numeric_limits<size_t>::max()};
  if (city.adj_list.empty()) { return {}; }

  AdjacenyPriorityQueue priorty_q{}; 
  std::vector<size_t> heat_losses(city.adj_list.size(), max_heat_loss);

  heat_losses[0] = 0;

  priorty_q.push()
    return {};
}
