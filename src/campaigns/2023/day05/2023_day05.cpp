#include "2023_day05.hpp"
#include <algorithm>
#include <limits>

Seeds build_seeds_vector(const std::string &line)
{
  constexpr int digits_start{ 7 };
  if (line.substr(0, digits_start) != "seeds: ") { return Seeds{}; }// NOLINT

  const std::string seed_digits{ line.substr(digits_start) };

  std::istringstream iss(seed_digits);
  Seeds seeds((std::istream_iterator<int64_t>(iss)), std::istream_iterator<int64_t>());
  return seeds;
}

size_t build_map(RangeMap &map, const AoCLib::line_data &data, size_t current_line)
{
  if (current_line >= data.size()) { return 0; }
  if (!map.empty()) { return 0; };
  if (current_line == 0) { return 0; }

  constexpr size_t range_min{ std::numeric_limits<size_t>::min() };
  constexpr size_t range_max{ std::numeric_limits<size_t>::max() };

  while (!data[current_line].empty()) {
    std::istringstream iss(data[current_line]);
    std::vector<size_t> range_data(
      (std::istream_iterator<size_t>(iss)), std::istream_iterator<size_t>());

    const GardenRange destination{ range_data[0], range_data[0] + range_data[2] - 1 };
    const GardenRange source{ range_data[1], range_data[1] + range_data[2] - 1 };

    map.emplace_back(source, destination);
    ++current_line;
    if (current_line == data.size()) { break; }
  }

  std::sort(map.begin(), map.end(), [](Mapping lead, Mapping next) {
    return (lead.first.first < next.first.first);
  });

  GardenRange unmapped{ range_min, range_min };
  if (map[0].first.first != range_min) {// we haven't started from zero so insert the first Mapping
    unmapped.second = map.front().first.first - 1;
    map.insert(map.begin(), { unmapped, unmapped });
  }

  for (auto iterator = map.begin(); iterator != map.end() - 1;
       ++iterator) {// fill in any mapping gaps
    auto next_mapping_start = (*iterator).first.second + 1;
    auto next_mapping_end = (*(iterator + 1)).first.first;

    if (next_mapping_start != next_mapping_end) {
      unmapped = GardenRange{ next_mapping_start, next_mapping_end - 1 };
      map.insert(iterator + 1, { unmapped, unmapped });
    }
  }

  unmapped = { map.back().first.second + 1, range_max };
  map.emplace_back(unmapped, unmapped);

  return current_line;
}

Catagories build_catagories(const AoCLib::line_data &data)
{
  if (data.empty()) { return Catagories{}; }

  size_t current_line{ 3 };
  Catagories catagories{};

  while (current_line < data.size()) {
    RangeMap map{};
    current_line = build_map(map, data, current_line);
    catagories.push_back(map);
    current_line += 2;
  }

  return catagories;
}

size_t trace_seed(size_t seed, const Catagories &catagories)
{
  if (catagories.empty()) { return 0; }

#ifdef CATCH2_ACTIVE
  std::cout << "starting seed: " << seed << std::flush;
#endif

  size_t next_mapping{ seed };
  for (const auto &search_map : catagories) {
    for (auto search_ranges : search_map) {
      const auto [source_start, source_end] = search_ranges.first;
      if (source_end >= next_mapping) {
        const auto [destination_start, destination_end] = search_ranges.second;
        const size_t offset(next_mapping - source_start);
        next_mapping = destination_start + offset;

#ifdef CATCH2_ACTIVE
        std::cout << " -> " << next_mapping << std::flush;
#endif
        break;
      }
    }
  }
#ifdef CATCH2_ACTIVE
  std::cout << '\n';
#endif

  return next_mapping;
}

SourceRanges build_seed_ranges(const std::string &line)
{
  if (line.empty()) { return SourceRanges{}; }

  constexpr int digits_start{ 7 };
  if (line.substr(0, digits_start) != "seeds: ") { return SourceRanges{}; }

  const std::string seeds_info{ line.substr(digits_start) };

  std::istringstream iss(seeds_info);
  Seeds seeds((std::istream_iterator<int64_t>(iss)), std::istream_iterator<int64_t>());

  SourceRanges seed_ranges{};
  for (size_t seeds_index{ 0 }; seeds_index < seeds.size(); seeds_index += 2) {
    seed_ranges.emplace_back(seeds[seeds_index], seeds[seeds_index] + seeds[seeds_index + 1] - 1);
  }

  std::sort(seed_ranges.begin(),
    seed_ranges.end(),
    [](const GardenRange first, const GardenRange last) { return first.second < last.first; });

  return seed_ranges;
}

RangeMap adjust_mapping(const SourceRanges &source_ranges, const RangeMap &next_level)
{
  if (source_ranges.empty() || next_level.empty()) { return RangeMap{}; }

  RangeMap range_map{};

  for (const auto &garden_range : source_ranges) {
    auto [range_start, range_end] = garden_range;
    for (const auto &mapping : next_level) {
      auto [source_start, source_end] = mapping.first;
      if (source_end < range_start) { continue; }
      auto [destination_start, destination_end] = mapping.second;
      Mapping new_map{ GardenRange{ range_start, 0 }, GardenRange{ 0, 0 } };
      const size_t start_offset = range_start - source_start;
      new_map.second.first = destination_start + start_offset;
      if (range_end < source_end) {
        new_map.first.second = range_end;
        const size_t end_offset = range_end - range_start;
        new_map.second.second = destination_start + start_offset + end_offset;
        range_map.push_back(new_map);
        break;
      } else { 
        new_map.first.second = source_end;
        const size_t end_offset = source_end - range_start;
        new_map.second.second = destination_start + start_offset + end_offset;
        range_map.push_back(new_map);
        range_start = source_end + 1;
      };
    }
  }

  return range_map;
}

LevelRanges level_ranges(const SourceRanges &seed_ranges, const Catagories &catagories)
{
  if (seed_ranges.empty() || catagories.empty()) { return LevelRanges{}; }
  return LevelRanges{};
}
