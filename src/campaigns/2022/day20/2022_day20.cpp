#include "2022_day20.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <fstream>

Items create_item_list(const AoCLib::int_data &data)
{
  if (data.empty()) { return Items{}; }

  Items items{};

  for (auto value : data) {
    const Item item{ value[0], false };
    items.push_back(item);
  }

  return items;
}

// NOLINTBEGIN(readability-function-cognitive-complexity)
void make_moves(Items &items)
{

  const int total_moves{ static_cast<int>(items.size()) };
  const int data_length{ static_cast<int>(items.size()) };
  const int last_position{ data_length - 1 };


  size_t current_position{ 0 };
  for (int move{ 0 }; move < total_moves; ++move) {
    const auto [data, already_moved] = items[current_position];
    if (already_moved) {
      ++current_position;
      --move;// this move doesn't count!
      continue;
    }

    if (data == 0) {
      items[current_position].second = true;
      ++current_position;
      continue;
    }

    const auto cycles{ std::div(data + static_cast<int>(current_position), last_position) };

    int new_position = cycles.rem;

    if (new_position < 0) { new_position = last_position + new_position; }
    if (new_position == 0 || new_position == last_position) {
      new_position = (new_position == 0) ? last_position : 0;
    }

    auto new_data_position{ static_cast<size_t>(new_position) };

    if (new_data_position > current_position) {// move forward
      for (auto source_position{ current_position }; source_position < new_data_position;
           ++source_position) {
        items[source_position] = items[source_position + 1];
      }
    } else {// move backward
      for (auto destination_position{ current_position }; destination_position > new_data_position;
           --destination_position) {
        items[destination_position] = items[destination_position - 1];
      }
      ++current_position;
    }
    items[new_data_position].first = data;
    items[new_data_position].second = true;
  }

  for (auto position{ 0 }; auto item : items) {
    if (!item.second) {
      std::cout << "missed " << item.first << " at position " << position << '\n';
    }
    ++position;
  }
}
// NOLINTEND(readability-function-cognitive-complexity)

int calculate_coordinate_sum(const Items &items)
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