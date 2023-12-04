#include "2023_day04.hpp"
#include <set>

void convert_raw_data_to_maps(const AoCLib::line_data &card_data,
  WinningsNumberMap &winning_numbers_map,
  CardNumberMap &card_numbers_map)
{
  if (card_data.empty()) { return; }

  for (int card_no{ 1 }; const auto &card : card_data) {
    std::vector<std::string> card_info{ AoCLib::split_string_at_delimter(card, ':') };
    std::vector<std::string> card_numbers{ AoCLib::split_string_at_delimter(card_info[1], '|') };

    CardNumbers winning_numbers{ AoCLib::string_to_vector(card_numbers[0]) };
    CardNumbers result_numbers{ AoCLib::string_to_vector(card_numbers[1]) };

    winning_numbers_map.emplace(card_no, winning_numbers);
    card_numbers_map.emplace(card_no, result_numbers);
    ++card_no;
  }
}

Winnings calculate_card_winnings(const CardNumbers &winners, const CardNumbers &numbers)
{
  if (winners.empty() or numbers.empty()) { return Winnings{ 0, 0 }; }

  std::set<int> all_numbers{};

  for (auto number : winners) { all_numbers.insert(number); }

  int prize_count{};
  int numbers_matched{};

  for (auto number : numbers) {
    if (all_numbers.insert(number).second) { continue; }

    if (prize_count == 0) {
      prize_count = 1;
    } else {
      prize_count *= 2;
    }

    numbers_matched++;
  }

  return Winnings{ numbers_matched, prize_count };
}

void inflate_card_copies(int current_card, CardCopies &card_copies, int cards_won) {
  if(cards_won == 0) {return;}

  const int no_of_winners{card_copies[static_cast<size_t>(current_card) - 1]};

  for(int copy{0}; copy < cards_won; ++copy) {
    const auto inflate_card_no{static_cast<size_t>(current_card + copy)};
    if(inflate_card_no >= card_copies.size()) {break;}
    card_copies[inflate_card_no] += no_of_winners;
  }
}
