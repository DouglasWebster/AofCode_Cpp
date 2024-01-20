#include "2023_day17.hpp"
#include <cstdlib>
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
        edge.heat_loss =
          static_cast<size_t>(data[static_cast<size_t>(dest_link.quot)][static_cast<size_t>(dest_link.rem)] - '0');
        edges.emplace_back(edge);
      }
    }
  }
  return edges;
}

constexpr size_t max_heat_loss{ std::numeric_limits<size_t>::max() };

struct CityBlock
{
  size_t total_heat_loss{max_heat_loss};
  size_t previous_block{max_block};
  Heading going{Nowhere};
  int previous_direction_count{0};
};

using CityBlockNode = std::pair<size_t, CityBlock>;

struct CB_Comparitor
{
  bool operator() (const CityBlockNode &lhs, const CityBlockNode &rhs)
  {
    return (lhs.second.total_heat_loss > rhs.second.total_heat_loss);
  }
};


ShortestPaths energy_used(const City &city)
{
  if (city.adj_list.empty()) { return {}; }

  std::priority_queue<CityBlockNode, std::vector<CityBlockNode>, CB_Comparitor> city_block_pq;

  std::vector<CityBlock> city_blocks(city.adj_list.size());
  city_blocks[0].total_heat_loss = 0;
  
  city_block_pq.emplace(0, city_blocks[0]);

  while (!city_block_pq.empty()) 
  {
    auto city_block = city_block_pq.top();
    city_block_pq.pop();
    size_t heat_loss_so_far = city_block.second.total_heat_loss;
    for(auto adjacency : city.adj_list[city_block.first]) {
      if(adjacency.dest == city_block.second.previous_block) {continue;}
      Heading going{adjacency.heading};
      Heading from{city_block.second.going};
      int heading_count = (going != from) ? 1 : city_block.second.previous_direction_count +1;
      if(heading_count > 3) {continue;}

      size_t next_block{adjacency.dest};

      size_t heat_loss_to_next_block = heat_loss_so_far + adjacency.heat_loss;
      size_t next_block_heat_losses{city_blocks[next_block].total_heat_loss};
      if((next_block_heat_losses == max_heat_loss) || (next_block_heat_losses > heat_loss_to_next_block)) {
        city_blocks[next_block].total_heat_loss = heat_loss_to_next_block;
        city_blocks[next_block].previous_block = city_block.first;
        city_blocks[next_block].going = going;
        city_blocks[next_block].previous_direction_count = heading_count;
        city_block_pq.emplace(next_block, city_blocks[next_block]);
      }

    }

  }
  

  return {};
}
