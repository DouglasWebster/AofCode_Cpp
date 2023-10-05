#include "2022_day03.hpp"
#include <algorithm>
#include <numeric>
#include <unordered_set>
#include <cassert>


Contents collate_contents(const AoCLib::str_data &raw_data)
{
  Contents contents{};

  if (raw_data.empty()) { return contents; }

  contents.resize(raw_data.size());

  std::transform(raw_data.begin(), raw_data.end(), contents.begin(), [](const auto &items) { return items[0]; });

  return contents;
}

Rucksack get_compartments(const std::string &contents)
{
  Rucksack rucksack{ "", "" };
  if (contents.empty()) { return rucksack; }
  if (contents.size() % 2 != 0) { return rucksack; }

  const size_t split_position{ contents.size() / 2 };

  rucksack.first = contents.substr(0, split_position);
  rucksack.second = contents.substr(split_position);

  return rucksack;
}

char find_common_item(const Rucksack &rucksack)
{
  if (rucksack == Rucksack("", "")) { return 0; }

  const std::unordered_set<char> compartment_1(rucksack.first.begin(), rucksack.first.end());
  const std::unordered_set<char> compartment_2(rucksack.second.begin(), rucksack.second.end());

  for (auto item : compartment_1) {
    if (compartment_2.contains(item)) { return item; }
  }

  return 0;
}

constexpr int upper_case_offset = 27;
constexpr int lower_case_offset = 1;
int calculate_priority(const char item)
{
  return (item >= 'a') ? (item - 'a' + lower_case_offset) : (item - 'A' + upper_case_offset);
}

int calculate_badges(const Contents &contents)
{
  int badge_priority{};
  if (contents.empty()) { return badge_priority; }

  using Groups = std::vector<Contents>;

  // create a vector of triplets of pack contents
  Groups groups{};
  Contents pack_items;

  for (int counter{ 1 }; const auto &pack : contents) {
    pack_items.push_back(pack);
    if (counter % 3 == 0) {
      groups.push_back(pack_items);
      pack_items.clear();
    }
    ++counter;
  }

  assert((pack_items.empty()) && "Unaccounted items in the pack");
  assert((!groups.empty()) && "groups should have at least 1 item");

  std::vector<char> badges;
  for (const auto &triplet : groups) {
    const std::unordered_set<char> set1(triplet[0].begin(), triplet[0].end());
    const std::unordered_set<char> set2(triplet[1].begin(), triplet[1].end());
    const std::unordered_set<char> set3(triplet[2].begin(), triplet[2].end());

    for (auto item : set1) {
      if (set2.contains(item) && set3.contains(item)) { badges.push_back(item); }
    }
  }

  badge_priority = std::accumulate(
    badges.begin(), badges.end(), 0, [](int accumulator, char item) { return accumulator + calculate_priority(item); });

  return badge_priority;
}
