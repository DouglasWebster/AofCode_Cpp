#include "2023_day17.hpp"
#include <cstdlib>
#include <format>
#include <functional>
#include <limits>
#include <queue>

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
        edge.heat_loss = static_cast<size_t>(
          data[static_cast<size_t>(dest_link.quot)][static_cast<size_t>(dest_link.rem)] - '0');
        edges.emplace_back(edge);
      }
    }
  }
  return edges;
}

constexpr size_t max_heat_loss{ std::numeric_limits<size_t>::max() };

struct CityBlock
{
  size_t total_heat_loss{ max_heat_loss };
  size_t previous_block{ max_block };
  Heading going{ Nowhere };
  int steps{ 1 };
};

using CityBlockNode = std::pair<size_t, CityBlock>;

struct CB_Comparitor
{
  bool operator()(const CityBlockNode &lhs, const CityBlockNode &rhs) const
  {
    return (lhs.second.total_heat_loss > rhs.second.total_heat_loss);
  }
};

void print_visited(const std::vector<CityBlock> &city_blocks)
{

  for (const auto &city_block : city_blocks) {
    if (city_block.total_heat_loss == max_heat_loss) { continue; }
    std::string going{};
    switch (city_block.going) {
    case North:
      going = "North";
      break;
    case South:
      going = "South";
      break;
    case East:
      going = "East";
      break;
    case West:
      going = "West";
      break;
    default:
      going = "Nowhere";
      break;
    };

    std::cout << std::format("Previous block: {}, Heat_loss: {}, Heading: {}, Steps: {}\n",
      city_block.previous_block,
      city_block.total_heat_loss,
      going,
      city_block.steps);
  }
}

ShortestPaths energy_used(const City &city, const int min_steps, const int max_steps)
{
  if (city.adj_list.empty()) { return {}; }
  const size_t city_block_space{ 4 * static_cast<size_t>(max_steps) };// space for 4 directions and max_steps per direction.
  const size_t block_count{ city.adj_list.size() };

  std::priority_queue<CityBlockNode, std::vector<CityBlockNode>, CB_Comparitor> city_block_pq;

  // visited blocks - reserve enought space for each block having 4 directions and up to 3 steps to
  // reach it. 
  std::vector<CityBlock> city_blocks(block_count * city_block_space);
  city_blocks[0].total_heat_loss = 0;

  city_block_pq.emplace(0, city_blocks[0]);

  while (!city_block_pq.empty()) {
    auto [block_id, block_data] = city_block_pq.top();
    city_block_pq.pop();
    const auto city_location{ block_id / city_block_space };
    if (city_location == block_count -1) {
       return { city_location, block_data.total_heat_loss }; }

    for (const auto &adjacency : city.adj_list[city_location]) {
      const auto current_dir{block_data.going};
      const auto next_heading{adjacency.heading};
      if (adjacency.dest == max_block) { continue; }
      if (current_dir != Nowhere && block_data.steps < min_steps && current_dir != next_heading) {continue;}
      if (block_data.steps >= max_steps && current_dir == next_heading) { continue; }
      switch (current_dir) {
      case North:
        if (next_heading == South) { continue; }
        break;
      case South:
        if (next_heading == North) { continue; }
        break;
      case East:
        if (next_heading == West) { continue; }
        break;
      case West:
        if (next_heading == East) { continue; }
        break;
      default:
        break;
      }

      const size_t next_block_base{ adjacency.dest * city_block_space };
      const int steps = (current_dir == next_heading) ? block_data.steps + 1 : 1;
      const auto offset = static_cast<size_t>(next_heading * max_steps + steps - 1);
      const size_t next_block_id{ next_block_base + offset };
      const size_t next_block_heat_loss{ city_blocks[next_block_id].total_heat_loss };
      const size_t heat_loss = block_data.total_heat_loss + adjacency.heat_loss;
      if (next_block_heat_loss == max_heat_loss || heat_loss < next_block_heat_loss) {
        CityBlock next_block{ heat_loss, block_id, next_heading, steps };
        city_blocks[next_block_id] = next_block;
        city_block_pq.emplace(next_block_id, next_block);
      }
    }
  }

  return {};
}
