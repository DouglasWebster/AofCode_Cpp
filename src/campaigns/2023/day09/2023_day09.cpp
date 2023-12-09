#include "2023_day09.hpp"
#include <algorithm>
#include <iterator>
#include <numeric>
#include <ranges>

History build_history(const Sequence &sequence)
{
  if (sequence.empty()) { return History{}; }

  Sequence next_sequence{ sequence };
  History sequence_history{ sequence };

  while (
    std::ranges::any_of(next_sequence.begin(), next_sequence.end(), [](int64_t item) { return item != 0; })) {
    const Sequence last_sequence{ next_sequence };
    next_sequence.clear();
    for (auto iter = last_sequence.begin(); iter != last_sequence.end() - 1; ++iter) {
      next_sequence.push_back(*(iter + 1) - *iter);
    }
    sequence_history.push_back(next_sequence);
  }

  return sequence_history;
}

void extrapolate_next_value(History &history)
{

  history.back().push_back(0);

  auto t_rit = history.rbegin();
  auto p_rit = history.rbegin() + 1;

  for (; p_rit != history.rend(); ++t_rit, ++p_rit) {
    (*p_rit).push_back((*t_rit).back() + (*p_rit).back());
  }
}

int64_t calculate_extrapolated_sum(const Tree &tree)
{
  if (tree.empty()) { return 0; }

  return std::accumulate(tree.begin(), tree.end(), 0, [](int64_t sum, const auto &history) {
    return sum + history.front().back();
  });
}
