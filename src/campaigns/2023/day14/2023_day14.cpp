#include "2023_day14.hpp"
#include <algorithm>

Platform create_platform(const AoCLib::char_data &puzzle_data)
{
  if (puzzle_data.empty()) { return Platform{}; }

  Platform platform{};
  for (const auto &data : puzzle_data) { platform.emplace_back(data); }

  return platform;
}

Platform transpose_platform(const Platform &platform)
{
  if (platform.empty()) { return Platform{}; }

  const size_t t_rows = platform[0].size();
  const size_t t_cols = platform.size();

  Platform transposed{ t_rows, Row(t_cols, '.') };

  for (size_t row{}; row < t_cols; ++row) {
    for (size_t col{}; col < t_rows; ++col) { transposed[col][row] = platform[row][col]; }
  }

  return transposed;
}

Platform tilt_platform(const Platform &platform, const Cardinal direction)
{
  if (platform.empty()) { return Platform{}; }
  if (direction != Cardinal::North) { return Platform{}; }

  Platform transposed{ transpose_platform(platform) };

  for (auto &row : transposed) {
    const std::vector<char> rock({ '#' });
    auto not_rock_it =
      std::find_if_not(row.begin(), row.end(), [](char item) { return item == '#'; });
    while (not_rock_it != row.end()) {
      const auto rock_it = std::find(not_rock_it, row.end(), '#');
      const long balls = std::count(not_rock_it, rock_it, 'O');
      const long spaces = std::count(not_rock_it, rock_it, '.');
      for (long ball{}; ball < balls; ++ball) { *not_rock_it++ = 'O'; }
      for (long space{}; space < spaces; ++space) { *not_rock_it++ = '.'; }
      not_rock_it = std::find_if_not(rock_it, row.end(), [](char item) { return item == '#'; });
    }
  }

  return transpose_platform(transposed);
}

int64_t calculate_load(const Platform &platform, const Cardinal support)
{
  if (platform.empty() || support != Cardinal::North) { return 0; }

  int64_t load_multiplier{static_cast<int64_t> (platform.size())};
  int64_t total_load{};
  for (const auto &row : platform) {
    const int64_t balls = std::count(row.begin(), row.end(), 'O');
    total_load += balls * load_multiplier;
    --load_multiplier;
  }

  return total_load;
}
