#include "2023_day15.hpp"

#include <algorithm>

size_t hash_step(const Step &step)
{
  constexpr int hash_value_1{ 17 };
  constexpr int hash_value_2{ 256 };
  if (step.empty()) { return 0; }

  size_t hash_value{};
  for (const auto character : step) {
    hash_value += static_cast<size_t>(character);
    hash_value *= hash_value_1;
    hash_value %= hash_value_2;
  }

  return hash_value;
}

HashMap create_hashmap(const AoCLib::line_data &puzzle_data)
{
  constexpr int hash_map_size{ 256 };
  if (puzzle_data.empty()) { return HashMap{}; }
  const Sequence sequence{ AoCLib::split_string_at_delimter(puzzle_data[0], ',') };

  HashMap hash_map(hash_map_size);

  for (const auto &step : sequence) {
    std::string label{};
    char hash_op{};
    int focal_length{};
    for (const auto character : step) {
      if (islower(character) != 0) {
        label.push_back(character);
        continue;
      }
      if (isdigit(character) != 0) {
        focal_length += focal_length * 10 + (character - '0');// NOLINT
        continue;
      }
      hash_op = character;
    }


    const size_t box_no{ hash_step(label) };
    Box &box{ hash_map[box_no] };
    if (hash_op == '-') {
      if (!box.empty()) {
        box.remove_if([label](Lens &lens) { return lens.first == label; });
      }
      continue;
    }

    auto lens_it =
      std::find_if(box.begin(), box.end(), [label](Lens &lens) { return lens.first == label; });

    if (lens_it == box.end()) {
      box.emplace_back(label, focal_length);
    } else {
      (*lens_it).second = focal_length;
    }
  }

  return hash_map;
}

size_t calc_focusing_power(const HashMap &hash_map)
{
  if (hash_map.empty()) { return 0; }

  constexpr int hash_map_size{ 256 };
  size_t focusing_power{};
  for (size_t box_no{ 1 }; box_no <= hash_map_size; ++box_no) {
    const Box &box{ hash_map[box_no - 1] };
    if (box.empty()) { continue; }
    size_t lens_power{};
    for (size_t index{ 1 }; const auto &lens : box) {
      lens_power += index * static_cast<size_t>(lens.second);
      ++index;
    }
    focusing_power += lens_power * box_no;
  }

  return focusing_power;
}
