#include "2022_day01.hpp"

#include <algorithm>
#include <numeric>

ElvenPacks collate_calories(const ElvenPacks &uncollated_packs)
{
  ElvenPacks elves_calories{};

  if (std::all_of(
        uncollated_packs.begin(), uncollated_packs.end(), [](const std::vector<int> &item) { return item.empty(); })) {
    return elves_calories;
  }

  if (std::any_of(uncollated_packs.begin(), uncollated_packs.end(), [](const std::vector<int> &item) {
        return (item.size() > 1);
      })) {
    return elves_calories;
  }

  std::vector<int> pack_calories{};
  for (auto item : uncollated_packs) {
    if (item.empty()) {
      elves_calories.push_back(pack_calories);
      pack_calories.clear();
      continue;
    }
    pack_calories.push_back(item[0]);
  }

  if (!pack_calories.empty()) { elves_calories.push_back(pack_calories); }

  return elves_calories;
}

PacksCalories sum_calories(const ElvenPacks &elven_packs)
{

  PacksCalories pack_totals{};

  for (const auto &pack : elven_packs) {
    const int total = std::accumulate(pack.begin(), pack.end(), 0);
    pack_totals.push_back(total);
  }

  return pack_totals;
}

int max_values(const ElvenPack &packs, int over)
{
  if (packs.empty() || over == 0) { return 0; }

  ElvenPack temp_vector = packs;

  std::ranges::sort(temp_vector, std::ranges::greater());

  const int total = std::accumulate(temp_vector.begin(), temp_vector.begin() + over, 0);

  return total;
}
