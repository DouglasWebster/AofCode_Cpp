#include "2023_day21.hpp"

void prevent_stepping_onto_stones(Garden &garden) {
  for(auto &tile : garden) {
    if(tile.north != max_location ){
      if(garden[tile.north].type == '#') {tile.north = max_location;}
    }
    if(tile.south != max_location ){
      if(garden[tile.south].type == '#') {tile.south = max_location;}
    }
    if(tile.east != max_location ){
      if(garden[tile.east].type == '#') {tile.east = max_location;}
    }
    if(tile.west != max_location ){
      if(garden[tile.west].type == '#') {tile.west = max_location;}
    }
  }
}

Garden create_garden(const AoCLib::char_data &data)
{
  if (data.empty()) { return {}; }

  const size_t rows{ data.size() };
  const size_t cols{ data[0].size() };

  Garden garden{ rows * cols };

  size_t row{};
  size_t col{};

  for (const auto &row_data : data) {
    for (const auto &col_data : row_data) {

      const size_t north_tile = row == 0 ? max_location : (row - 1) * cols + col;
      const size_t south_tile = row == rows - 1 ? max_location : (row + 1) * cols + col;
      const size_t east_tile = col == cols - 1 ? max_location : row * cols + col + 1;
      const size_t west_tile = col == 0 ? max_location : row * cols + col - 1;

      auto &tile{ garden[row * cols + col] };
      
      tile.location = row * cols + col;
      tile.type = col_data;

      tile.north = north_tile;
      tile.south = south_tile;
      tile.east = east_tile;
      tile.west = west_tile;

      ++col;
    }
    ++row;
    col = 0;
  }

  prevent_stepping_onto_stones(garden);

  return garden;
}

void make_move(Possibles &possibles, const Garden &garden) {
  std::vector<size_t> current_locations{};

  for(const auto location : possibles) {
    current_locations.push_back(location);
  }

  // lets start again with the new locations
  possibles.clear();

  // make a move, even onto rocks!
  for(const auto &location : current_locations) {
    possibles.emplace(garden[location].north);
    possibles.emplace(garden[location].south);
    possibles.emplace(garden[location].east);
    possibles.emplace(garden[location].west);
  }

  // get rid of the moves onto rocks.
  possibles.erase(max_location);
}
