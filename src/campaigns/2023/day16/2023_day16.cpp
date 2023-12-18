#include "2023_day16.hpp"

void draw_energised(const Contraption &contraption)
{
  constexpr int row_start{ 10 };
  for (const auto &tile : contraption) {
    if ((static_cast<int>(tile.tile_id) % row_start) == 0) 
      { std::cout << '\n'; }
    const char item = tile.energised ? '#' : '.';
    std::cout << item;
  }
  std::cout << '\n';
}

Contraption build_contaption(const AoCLib::char_data &puzzle_data)
{
  if (puzzle_data.empty()) { return Contraption{}; }


  const size_t rows = puzzle_data.size();
  const size_t cols = puzzle_data[0].size();


  Contraption contraption(rows * cols);

  size_t row{};
  size_t col{};

  for (const auto &row_data : puzzle_data) {
    for (const auto &col_data : row_data) {

      const size_t north_tile = row == 0 ? no_tile : (row - 1) * cols + col;
      const size_t south_tile = row == rows - 1 ? no_tile : (row + 1) * cols + col;
      const size_t east_tile = col == cols - 1 ? no_tile : row * cols + col + 1;
      const size_t west_tile = col == 0 ? no_tile : row * cols + col - 1;

      auto &tile{ contraption[row * cols + col] };

      // default exits to pass through
      tile.tile_id = row * cols + col;
      tile.tile_type = col_data;

      tile.n_tile = tile.n_link = north_tile;
      tile.s_tile = tile.s_link = south_tile;
      tile.e_tile = tile.e_link = east_tile;
      tile.w_tile = tile.w_link = west_tile;
      switch (col_data) {
      case '.':
        break;
      case '-':
        tile.n_tile = tile.n_link = tile.s_tile = tile.s_link = no_tile;
        tile.going_north = tile.going_south = ExitDirections{ Direction::East, Direction::West };
        break;
      case '|':
        tile.e_tile = tile.e_link = tile.w_tile = tile.w_link = no_tile;
        tile.going_east = tile.going_west = ExitDirections{ Direction::North, Direction::South };
        break;
      case '\\':
        // tile.n_tile = tile.n_link = east_tile;
        // tile.s_tile = tile.s_link = west_tile;
        // tile.e_tile = tile.e_link = north_tile;
        // tile.w_tile = tile.w_link = south_tile;
        tile.going_north = ExitDirections{ Direction::West, Direction::None };
        tile.going_south = ExitDirections{ Direction::East, Direction::None };
        tile.going_east = ExitDirections{ Direction::South, Direction::None };
        tile.going_west = ExitDirections{ Direction::North, Direction::None };
        break;
      case '/':
        // tile.n_tile = tile.n_link = west_tile;
        // tile.s_tile = tile.s_link = east_tile;
        // tile.e_tile = tile.e_link = south_tile;
        // tile.w_tile = tile.w_link = north_tile;
        tile.going_north = ExitDirections{ Direction::East, Direction::None };
        tile.going_south = ExitDirections{ Direction::West, Direction::None };
        tile.going_east = ExitDirections{ Direction::North, Direction::None };
        tile.going_west = ExitDirections{ Direction::South, Direction::None };
        break;

      default:
        break;
      }
      ++col;
    }
    ++row;
    col = 0;
  }


  return contraption;
}

Exit Tile::transit_tile(Direction direction)
{
  // don't go back the way we've come.
  Direction entry_direction{ Direction::None };
  switch (direction) {
  case Direction::North:
    entry_direction = Direction::South;
    break;
  case Direction::South:
    entry_direction = Direction::North;
    break;
  case Direction::East:
    entry_direction = Direction::West;
    break;
  case Direction::West:
    entry_direction = Direction::East;
    break;
  default:
    break;
  }
  size_t *entry_link(match_tile_to_direction(entry_direction));
  *entry_link = no_tile;


  ExitDirections exits{};

  switch (direction) {
  case Direction::North:
    exits = going_north;
    break;
  case Direction::South:
    exits = going_south;
    break;
  case Direction::East:
    exits = going_east;
    break;
  case Direction::West:
    exits = going_west;
    break;
  default:
    break;
  }

    energised = true;

  size_t *exit_link{};

  if (exits.first != Direction::None) {
    exit_link = match_tile_to_direction(exits.first);
    if (*exit_link != no_tile) {
      const size_t link_tile = *exit_link;
      *exit_link = no_tile;
      return Exit{ link_tile, exits };
    }
    exits.first = Direction::None;
  }

  if (exits.second != Direction::None) {
    exit_link = match_tile_to_direction(exits.second);
    if (*exit_link != no_tile) {
      const size_t link_tile = *exit_link;
      *exit_link = no_tile;
      return Exit{ link_tile, exits };
    }
  }

  return Exit{};
}

size_t *Tile::match_tile_to_direction(const Direction direction)
{
  size_t *tile{ &this->void_tile };
  switch (direction) {
  case Direction::North:
    tile = &(this->n_tile);
    break;
  case Direction::South:
    tile = &(this->s_tile);
    break;
  case Direction::East:
    tile = &(this->e_tile);
    break;
  case Direction::West:
    tile = &(this->w_tile);
    break;

  default:
    break;
  }
  return tile;
}

bool Tile::more_exits() const
{
  switch (tile_type) {
  case '|':
    return (n_tile != no_tile || s_tile != no_tile);
  case '-':
    return (e_tile != no_tile || w_link != no_tile);
  default:
    return (n_tile != no_tile || s_tile != no_tile || e_tile != no_tile || w_tile != no_tile);
  }
  return true;
}

Exit Tile::get_last_exit()
{
  if (n_tile != no_tile) {
    return Exit{ n_tile, ExitDirections(Direction::North, Direction::None) };
  }
  if (s_tile != no_tile) {
    return Exit{ s_tile, ExitDirections(Direction::South, Direction::None) };
  }
  if (e_tile != no_tile) {
    return Exit{ e_tile, ExitDirections(Direction::East, Direction::None) };
  }
  if (w_tile != no_tile) {
    return Exit{ w_tile, ExitDirections(Direction::West, Direction::None) };
  }

  return Exit{};
}


void do_light_beam(Contraption &contraption, size_t tile_id, Direction direction)
{
  NextMirrors to_visit{};

  while (tile_id != no_tile) {
    Tile &current_tile{ contraption[tile_id] };
    const Exit exit{ current_tile.transit_tile(direction) };
    // draw_energised(contraption);
    direction =
      exit.directions.first == Direction::None ? exit.directions.second : exit.directions.first;
    tile_id = exit.tile_id;

    if (current_tile.tile_type == '|' || current_tile.tile_type == '-') {
      if (current_tile.more_exits()) 
        { to_visit.push(current_tile.tile_id); }
    }

    if (tile_id == no_tile ) {
      if(to_visit.empty()) {break;} // no where to go so finish!    
      Exit new_exit = contraption[to_visit.top()].get_last_exit();
      to_visit.pop();
      while(new_exit.tile_id == no_tile && !to_visit.empty()) {
        new_exit = contraption[to_visit.top()].get_last_exit();
        to_visit.pop();
      }
      direction = new_exit.directions.first;
      tile_id = new_exit.tile_id;
      continue;
    }
  }
}

