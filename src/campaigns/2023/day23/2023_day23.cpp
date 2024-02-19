#include "2023_day23.hpp"
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <limits>
#include <list>
#include <map>
#include <math.h>
#include <queue>
#include <set>

void list_nodes(TrailGraph trail_graph, int width)
{
  std::string data_file = CURRENT_LIST_DIR;
  data_file += "/nodes.txt";

  std::ofstream file_dump;
  file_dump.open(data_file, std::ofstream::out | std::ofstream::trunc);
  for (auto node : trail_graph) {
    auto location = std::div(static_cast<int>(node.first), width);
    int index = static_cast<int>(node.first);
    file_dump << " Node index: " << std::setw(5) << index << ", Row: " << std::setw(3)
              << location.quot + 1 << ", Column: " << std::setw(3) << location.rem + 1 << '\n';
  }
  file_dump << '\n';
  file_dump.close();
}

void create_digraph(const TrailGraph &graph,
  const std::vector<size_t> &order,
  const std::vector<int> &travelled)
{
  std::string data_file = CURRENT_LIST_DIR;
  data_file += "/digraph.txt";

  std::ofstream out_file;
  out_file.open(data_file, std::ofstream::out | std::ofstream::trunc);

  out_file << "digraph finite_state_machine {\n";
  out_file << "fontname=\"Helvetica,Arial,sans-serif\"\n";
  out_file << "node [fontname=\"Helvetica,Arial,sans-serif\"]\n";
  out_file << "edge [fontname=\"Helvetica,Arial,sans-serif\"]\n";
  out_file << "rankdir=LR;\n";
  out_file << "node [shape = doublecircle]; " << order.front() << " " << order.back() << ";\n";
  out_file << "node [shape = circle];\n";

  for (auto index : order) {
    for (auto node : graph.at(index)) {
      auto [node_id, weight] = node;
      auto so_far = travelled[index] + weight;
      out_file << index << " -> " << node_id << " [label = \"" << weight << "(" << so_far
               << ")\"];\n";
    }
  }
  out_file << "}\n";
  out_file.close();
}


TrailMap build_trails(const AoCLib::char_data data)
{
  if (data.empty()) {
    return {};
  }

  const size_t rows{ data.size() };
  const size_t cols{ data[0].size() };

  TrailMap trail_map{};
  trail_map.reserve(rows * cols);

  for (size_t row{}; row < rows; ++row) {
    for (size_t col{}; col < cols; ++col) {
      const size_t north_step = row == 0 ? max_location : (row - 1) * cols + col;
      const size_t south_step = row == rows - 1 ? max_location : (row + 1) * cols + col;
      const size_t east_step = col == cols - 1 ? max_location : row * cols + col + 1;
      const size_t west_step = col == 0 ? max_location : row * cols + col - 1;

      Location location{};
      location.index = row * rows + col;
      char current_position{ data[row][col] };
      if (current_position == '#') {
        trail_map.emplace_back(location);
        continue;
      }
      switch (current_position) {
      case '^':
        location.North = north_step;
        location.exits = 1;
        break;
      case 'v':
        location.South = south_step;
        location.exits = 1;
        break;
      case '>':
        location.East = east_step;
        location.exits = 1;
        break;
      case '<':
        location.West = west_step;
        location.exits = 1;
        break;
      default:// must be a path
        int exits{};
        char n_char = (north_step == max_location) ? '#' : data[row - 1][col];
        if (n_char != '#' && n_char != 'v' ) {
          location.North = north_step;
          ++exits;
        }
        char s_char = (south_step == max_location) ? '#' : data[row + 1][col];
        if (s_char != '#' && s_char != '^' ) {
          location.South = south_step;
          ++exits;
        }
        char e_char = (east_step == max_location) ? '#' : data[row][col + 1];
        if (e_char != '#' && e_char != '<' ) {
          location.East = east_step;
          ++exits;
        }

        char w_char = (west_step == max_location) ? '#' : data[row][col - 1];
        if (w_char != '#' && w_char != '>') {
          location.West = west_step;
          ++exits;
        }
        location.exits = exits;
      }

      trail_map.emplace_back(location);
    }
  }
  return trail_map;
}

/**
 * @brief get the location of the next node and the number of steps
 * taken to reach it.
 *
 * @param trail_map the vector of locations with the permisable steps.
 * @param start the location of the *first* step from the previous node.
 * @param node the starting node location for this search.
 * @return TrailEdge
 */
TrailEdge find_next_node(const TrailMap &trail_map, size_t start, size_t node)
{
  int steps{ 1 };// already had one step
  bool not_node{ true };
  std::set<size_t> visited({ node, start });

  while (not_node) {
    auto possible{ trail_map[start].to_visit() };
    int exits{};
    size_t next{ max_location };
    for (auto item : possible) {
      if (visited.find(item) == visited.end()) {
        ++exits;
        next = item;
      }
    }
    if (exits != 1) {
      not_node = false;
      continue;
    }
    ++steps;
    start = next;
    visited.emplace(start);
  }
  return { start, steps };
}

TrailGraph build_trail_graph(const TrailMap &trail_map)
{
  if (trail_map.empty()) {
    return {};
  }

  size_t start{ 1 };
  size_t end{ trail_map.size() - 2 };
  TrailGraph trail_graph{};
  using visiting = std::pair<size_t, size_t>;
  std::vector<bool> visited(trail_map.size(), false);
  std::queue<visiting> to_visit{};

  std::map<size_t, size_t> node_order{};
  size_t insert_count{};

  for (const auto next : trail_map[start].to_visit()) {
    to_visit.emplace(start, next);
  }

  while (!to_visit.empty()) {
    auto [node_index, next] = to_visit.front();
    to_visit.pop();
    if (node_index == end) {
      continue;
    }
    auto [next_index, steps] = find_next_node(trail_map, next, node_index);
    if (next_index != max_location) {
      auto trail_graph_item{ trail_graph.find(node_index) };
      if (trail_graph_item == trail_graph.end()) {
        node_order.emplace(node_index, insert_count++);
        trail_graph.emplace(node_index, TrailEdges{});
      }
      bool stored{ false };
      for (auto check : trail_graph[node_index]) {
        if (check.first == next_index && check.second == steps) {
          stored = true;
        }
      }
      if (!stored) {
        trail_graph[node_index].emplace_back(next_index, steps);
        for (const auto possible : trail_map[next_index].to_visit()) {
          to_visit.emplace(next_index, possible);
        }
      }
    }
  }

  node_order.emplace(end, insert_count);

  list_nodes(trail_graph, static_cast<int>(std::sqrt(trail_map.size())));

  TrailGraph normalised_graph{};
  for (auto node : trail_graph) {
    auto edges = node.second;
    for (auto &edge : edges) {
      edge.first = node_order[edge.first];
    }
    normalised_graph.emplace(node_order[node.first], edges);
  }
  normalised_graph.emplace(std::prev(node_order.end())->second, TrailEdges{});


  return normalised_graph;
}

/**
 * @brief given a TrailGraph with the the adjacencies listing only outgoing connections
 * convert it to a TrailGraph with the adjacencies listing only incoming connections
 *
 * @param trail_graph
 * @return TrailGraph
 */
TrailGraph convert_to_incomming_edges(const TrailGraph &trail_graph)
{
  TrailGraph by_incomming{};
  for (size_t index{}; index < trail_graph.size(); ++index) {
    by_incomming.emplace(index, TrailEdges{});
  }

  for (const auto &[source, edges] : trail_graph) {
    for (const auto &[destination, weight] : edges) {
      by_incomming[destination].emplace_back(source, weight);
    }
  }

  return by_incomming;
}

std::vector<size_t> topological_sort(const TrailGraph &trail_graph)
{
  if (trail_graph.empty()) {
    return {};
  }

  size_t nodes{ trail_graph.size() };

  TrailGraph by_incomming{ convert_to_incomming_edges(trail_graph) };
  std::vector<size_t> sorted{};
  std::vector<size_t> indegrees(nodes, 0);
  std::queue<size_t> zero_incoming{};

  for (const auto &[node, edges] : by_incomming) {
    indegrees[node] = edges.size();
  }

  size_t visited_nodes{};

  for (const auto &[node, _] : by_incomming) {
    if (indegrees[node] == 0) {
      zero_incoming.push(node);
      visited_nodes++;
    }
  }

  while (!zero_incoming.empty()) {
    size_t node{ zero_incoming.front() };
    zero_incoming.pop();
    sorted.push_back(node);
    auto edges = trail_graph.at(node);
    for (auto [next_node, _] : edges) {
      if (--indegrees[next_node] == 0) {
        zero_incoming.push(next_node);
        visited_nodes++;
      }
    }
  }

  if (visited_nodes != nodes) {
    std::cout << "Graph is not acyclic!";
    return {};
  }

  return sorted;
}

int longest_path(const TrailGraph &trail_graph, const std::vector<size_t> &order)
{
  if (trail_graph.empty()) {
    return 0;
  }

  constexpr int INF = std::numeric_limits<int>::min();
  std::vector<int> travelled(trail_graph.size(), INF);
  travelled[0] = 0;
  for (auto node : order) {
    if (travelled[node] != INF) {
      for (const auto &adj_nodes : trail_graph.at(node)) {
        auto [adj_node, weight] = adj_nodes;
        if (travelled[adj_node] < travelled[node] + weight) {
          travelled[adj_node] = travelled[node] + weight;
        }
      }
    }
  }

  create_digraph(trail_graph, order, travelled);

  return travelled.back();
}
