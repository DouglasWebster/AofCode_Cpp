#include "2023_day12.hpp"
#include <algorithm>
#include <numeric>

int first_item_fits(const Springs &springs, const DamagedGroups &groups)
{
  if (springs.empty() || groups.empty()) { return 0; }

  std::string match_string{ springs };

  std::string matching_string(groups.front(), '#');
  matching_string.push_back('.');

  std::string back_end{};
  for (size_t group_index{ 1 }; group_index < groups.size(); ++group_index) {
    back_end += std::string(groups[group_index], '#');
    back_end.push_back('.');
  }
  back_end.pop_back();

  int fits{};
  while (true) {
    //find the first position of the first spring group.
    auto str_iter = std::search(match_string.begin(),
      match_string.end(),
      matching_string.begin(),
      matching_string.end(),
      [](char char_1, char char_2) {
        if (char_1 == '#') { return (char_2 == '#' || char_2 == '?'); }
        return (char_2 == '?' || char_2 == '.');
      });

    if (str_iter == match_string.end()) { break; } // can't find it so stop;
    const size_t next_position = static_cast<size_t> (str_iter - match_string.begin());
    const std::string remainder{match_string.substr(next_position + matching_string.size())};
    if(remainder.size() <= back_end.size()) {break;}

    auto back_iter = std::search(remainder.begin(),
      remainder.end(),
      back_end.begin(),
      back_end.end(),
      [](char char_1, char char_2) {
        if (char_1 == '?') { return true; }
        if (char_1 == '#') { return (char_2 == '#' || char_2 == '?'); }
        return (char_2 == '?' || char_2 == '.');
      });
    if (back_iter == remainder.end()) { break; }
    fits++;
    match_string.erase(0, next_position);
  }

  return fits;
}
