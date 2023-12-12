#include "2023_day11.hpp"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <cmath>

void dump_universe(const Universe &universe)
{
  std::string data_file = CURRENT_LIST_DIR;
  data_file += "/universe_dump.txt";

  std::ofstream universe_dump;
  universe_dump.open(data_file, std::ofstream::out | std::ofstream::trunc);

  for (const auto &row : universe) {
    for(const auto &col : row) {
      universe_dump << col;
    }
    universe_dump << '\n';
  }
  universe_dump.close();
}

Universe transpose_universe(Universe &universe)
{
  const size_t t_rows = universe[0].size();
  const size_t t_cols = universe.size();

  Universe transposed{ t_rows, std::vector<char>(t_cols, '.') };

  for (size_t row{}; row < t_cols; ++row) {
    for (size_t col{}; col < t_rows; ++col) { transposed[col][row] = universe[row][col]; }
  }

  return transposed;
}

void expand_universe(Universe &universe)
{

  Universe transpose_1{ transpose_universe(universe) };
  Universe expanded_1{};
  for (auto row : transpose_1) {
    expanded_1.push_back(row);
    if (std::none_of(row.begin(), row.end(), [](char galaxy) { return galaxy == '#'; })) {
      expanded_1.push_back(row);
    }
  }

  transpose_1 = transpose_universe(expanded_1);
  Universe expanded_2;
  ;
  for (auto row : transpose_1) {
    expanded_2.push_back(row);
    if (std::none_of(row.begin(), row.end(), [](char galaxy) { return galaxy == '#'; })) {
      expanded_2.push_back(row);
    }
  }

  universe = expanded_2;
}

Galaxies get_galaxies(const Universe &universe)
{
  if (universe.empty()) { return Galaxies{}; }

  Galaxies galaxies{};

  int galaxy_no{ 1 };
  for (size_t row_index{}; const auto &row : universe) {
    for (size_t col_index{}; const auto &item : row) {
      if (item == '#') {
        galaxies.emplace_back(galaxy_no, std::make_pair(row_index, col_index));
        ++galaxy_no;
      }
      ++col_index;
    }
    ++row_index;
  }
  return galaxies;
}

GalaxyPairs pair_galaxies(const Galaxies &galaxies) {
  if (galaxies.empty()) { return GalaxyPairs{}; }

  GalaxyPairs pairs{};

  const int no_of_galaxies{ static_cast<int>(galaxies.size()) };

  for (int first{}; first < no_of_galaxies; ++first) {
    for (int second{ first + 1 }; second < no_of_galaxies; ++second) {
      pairs.emplace_back(first, second);
    }
  }
  return pairs;
}

int calculate_galaxy_manhattan_seperation(const GalaxyPairs &pairs, const Galaxies &galaxies)
{
    int manhattan_distance{};
  for (const auto &pair : pairs) {
    const std::pair<size_t, size_t> first_location{ galaxies[pair.first].second };
    const std::pair<size_t, size_t> second_location{ galaxies[pair.second].second };

    const int y_distance{abs((static_cast<int>(first_location.first) - static_cast<int>(second_location.first)))};
    const int x_distance{abs((static_cast<int>(first_location.second) - static_cast<int>(second_location.second)))};

    manhattan_distance += y_distance + x_distance;
  };

return manhattan_distance;
}
