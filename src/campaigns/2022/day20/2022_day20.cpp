#include "2022_day20.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <fstream>
#include <numeric>

auto create_item_vectors(const AoCLib::int_data &data) -> std::tuple<Items, Locations>
{
  if (data.empty()) { return { Items{}, Locations{} }; }

  Items items{};

  for (auto start_position{ 0 }; auto value : data) {
    const Item item{ value[0], start_position };
    items.push_back(item);
    ++start_position;
  }

  Locations locations(items.size());
  std::iota(locations.begin(), locations.end(), 0);


  return { items, locations };
}

//  NOLINTBEGIN(readability-function-cognitive-complexity, useStlAlgorithm)
void make_moves(Items &items, Locations &locations)
{
  const auto data_length{ items.size() };
  const auto last_position{ data_length - 1 };

#ifdef CATCH2_ACTIVE
  const int64_t first_value{ items[locations.front()].first };
  const int64_t last_value{ items[locations.back()].first };
  size_t zero_position{ 0 };
  
  for (auto location : locations) {
    if (items[location].first == 0) { zero_position = items[location].second; }  // cppcheck-suppress useStlAlgorithm
  }

  std::cout << "Tracking " << first_value << ", " << last_value << " and 0 at position " << zero_position << '\n';
#endif

  for (auto check_value{ 0 }; auto item_position : locations) {
    auto [data, original_position] = items[item_position];

    assert(check_value == static_cast<int>(original_position));
    ++check_value;

    if (data == 0) { continue; }// no movement so move on to the next.

    const auto cycles{ std::ldiv(
      data + static_cast<int64_t>(item_position), static_cast<int64_t>(last_position)) };
    auto new_position = cycles.rem;

    if (new_position < 0) { new_position = static_cast<int>(last_position) + new_position; }
    if (new_position == 0 || new_position == static_cast<int>(last_position)) {
      new_position = (new_position == 0) ? static_cast<int>(last_position) : 0;
    }

    auto new_abs_position = static_cast<size_t>(new_position);  // just to avoid lots of static_casts;

    if (new_abs_position > item_position) {// move forward by moving items above it down.
      for (auto source_position{ item_position }; source_position < new_abs_position;
           ++source_position) {
        items[source_position] = items[source_position + 1];
        locations[items[source_position + 1].second] = source_position;
      }
    } else {// move backward by moving items below it up
      for (auto destination_position{ item_position }; destination_position > new_abs_position;
           --destination_position) {
        items[destination_position] = items[destination_position - 1];
        locations[items[destination_position - 1].second] = destination_position;
      }
    }
    items[new_abs_position].first = data;
    items[new_abs_position].second = original_position;
    locations[original_position] = new_abs_position;
  }

#ifdef CATCH2_ACTIVE
  std::cout << "result : {";
  for (auto item : items) { std::cout << '{' << item.first << ", " << item.second << "}, "; }
  std::cout << "\b\b}\n";

  assert(items[locations.front()].first == first_value);
  assert(items[locations.back()].first == last_value);
  assert(items[locations[zero_position]].first == 0);
#endif
}
// NOLINTEND(readability-function-cognitive-complexity, useStlAlgorithm)

Value calculate_coordinate_sum(const Items &items)
{
  constexpr int offset_1{ 1000 };
  constexpr int offset_2{ 2000 };
  constexpr int offset_3{ 3000 };

  const auto items_size{ static_cast<int>(items.size()) };
  int zero_position{};
  for (auto item : items) {
    if (item.first == 0) { break; }
    ++zero_position;
  }

  const auto first_coord_pos = static_cast<size_t>((zero_position + offset_1) % items_size);
  const auto second_coord_pos = static_cast<size_t>((zero_position + offset_2) % items_size);
  const auto third_coord_pos = static_cast<size_t>((zero_position + offset_3) % items_size);

  return items[first_coord_pos].first + items[second_coord_pos].first
         + items[third_coord_pos].first;
}

void apply_decryption_key(Items &items, int64_t key) {
  for (auto &item : items ) {
    item.first *= key;
  }
}
