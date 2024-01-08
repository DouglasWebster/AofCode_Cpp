#include "2023_day02.hpp"

#include <algorithm>
#include <numeric>


// NOLINTBEGIN(readability-function-cognitive-complexity)
Games build_games(const AoCLib::line_data &raw_data)
{
  if (raw_data.empty()) { return Games{}; }

  Games games{};
  for (const auto &line : raw_data) {
    std::vector<std::string> data{};
    const size_t line_split{ line.find_first_of(':') };
    data.push_back(line.substr(0, line_split));
    data.push_back(line.substr(line_split + 2));

    Game game{};
    game.game_no = std::stoi(data[0].substr(5));// NOLINT
    auto shows{ AoCLib::split_string_at_delimter(data[1], ';') };
    Reveal reveal{};
    for (const auto &show : shows) {
      auto cubes{ AoCLib::split_string_at_delimter(show, ',') };
      for (const auto &cube : cubes) {
        auto cube_details{ AoCLib::split_string_at_delimter(cube, ' ') };
        auto colour{ cube_details[1][0] };
        CubeSet cube_set{};
        const int cube_count{ stoi(cube_details[0]) };
        switch (colour) {
        case 'b':
          cube_set.first = Cube::blue;
          if (cube_count > game.min_blue) { game.min_blue = cube_count; }
          break;
        case 'g':
          cube_set.first = Cube::green;
          if (cube_count > game.min_green) { game.min_green = cube_count; }
          break;
        case 'r':
          cube_set.first = Cube::red;
          if (cube_count > game.min_red) { game.min_red = cube_count; }
          break;
        default:
          break;
        }
        cube_set.second = cube_count;
        reveal.push_back(cube_set);
      }
      game.reveals.push_back(reveal);
      reveal.clear();
    }
    games.push_back(game);
  }
  return games;
}

int count_possible_games(const Games &games)
{
  constexpr int max_blue{ 14 };
  constexpr int max_green{ 13 };
  constexpr int max_red{ 12 };
  int possible_count{};

  for (const auto &game : games) {
    bool impossible{ false };
    for (const auto &reveal : game.reveals) {
      for (const auto &[cube_colour, cube_count] : reveal) {
        switch (cube_colour) {
        case Cube::blue:
          if (cube_count > max_blue) { impossible = true; }
          break;
        case Cube::green:
          if (cube_count > max_green) { impossible = true; }
          break;
        case Cube::red:
          if (cube_count > max_red) { impossible = true; }
          break;
        default:
          break;
        }
        if (impossible) { continue; }
      }
      if (impossible) { continue; }
    }
    if (!impossible) { possible_count += game.game_no; }
  }
  return possible_count;
}
// NOLINTEND(readability-function-cognitive-complexity)

int sum_set_powers(const Games &games)
{
  if (games.empty()) { return 0; }
  
  return std::accumulate(games.begin(), games.end(), 0, [](int x, auto &game) {
    return x + game. min_blue * game.min_green * game.min_red;
  });
}