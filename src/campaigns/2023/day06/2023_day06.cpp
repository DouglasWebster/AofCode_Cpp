#include "2023_day06.hpp"

Races get_races(const AoCLib::line_data &data)
{
  if (data.empty()) { return Races{}; }

  Races races{};
  AoCLib::line_data details{ AoCLib::split_string_at_delimter(data[0], ':') };

  std::istringstream timess(details[1]);
  std::vector<int> race_time((std::istream_iterator<int>(timess)), std::istream_iterator<int>());

  details = AoCLib::split_string_at_delimter(data[1], ':');
  std::istringstream distss(details[1]);
  std::vector<int> race_distance(
    (std::istream_iterator<int>(distss)), std::istream_iterator<int>());

  for (size_t index{ 0 }; index < race_time.size(); ++index) {
    const Race race{ race_time[index], race_distance[index] };
    races.push_back(race);
  }

  return races;
}

int64_t find_max_hold_time(const Race &race)
{
  auto [time_allowed, previous_max_dist] = race;
  if (time_allowed == 0) { return 0; }

  int64_t hold_time = time_allowed / 2;
  int64_t race_time = time_allowed - hold_time;

  int64_t distance_travelled = race_time * hold_time;
  while (distance_travelled > previous_max_dist) {
    ++hold_time;
    --race_time;
    distance_travelled = hold_time * race_time;
  }

  return hold_time - 1;
}

int64_t calc_number_of_winning_ways(const Race &race, const int64_t max_hold_time)
{
  if (max_hold_time == 0) { return 0; }

  const int64_t total_time{ race.first };
  const int64_t min_hold_time = total_time - max_hold_time;

  return max_hold_time - min_hold_time + 1;
}
