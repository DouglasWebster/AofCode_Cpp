#include "2023_day07.hpp"
#include <algorithm>
#include <iterator>
#include <map>
#include <numeric>


Hands build_hands(const AoCLib::line_data &hands_data)
{

  if (hands_data.empty()) { return Hands{}; }

  constexpr int Ace{ 14 };
  constexpr int King{ 13 };
  constexpr int Queen{ 12 };
  constexpr int Jack{ 11 };
  constexpr int Ten{ 10 };

  Hands hands;
  for (const auto &hand_data : hands_data) {
    if (hand_data.empty()) { continue; }
    AoCLib::line_data details{ AoCLib::split_string_at_delimter(hand_data, ' ') };
    Cards cards{};
    for (auto detail : details[0]) {
      switch (detail) {
      case 'A':
        cards.push_back(Ace);
        break;
      case 'K':
        cards.push_back(King);
        break;
      case 'Q':
        cards.push_back(Queen);
        break;
      case 'J':
        cards.push_back(Jack);
        break;
      case 'T':
        cards.push_back(Ten);
        break;
      default:
        cards.push_back(detail - '0');
        break;
      }
    };

    std::sort(cards.begin(), cards.end(), [](auto card1, auto card2) { return card1 > card2; });


    const Hand hand{ cards, stoi(details[1]) };
    hands.push_back(hand);
  }
  return hands;
}

void order_hands_by_bid(Hands &hands)
{
  if (hands.empty()) { return; }

  for (auto &hand : hands) {
    std::map<int, int> card_count;
    std::pair<std::map<int, int>::iterator, bool> ret;
    for (auto card : hand.cards) {
      ret = card_count.insert(std::pair(card, 1));
      if (!ret.second) { ret.first->second += 1; }
    }

    int max_no_card{};
    for (const auto &item : card_count) {
      if (item.second > max_no_card) { max_no_card = item.second; }
    }

    switch (card_count.size()) {
    case 1:
      hand.strength = HandStrength::Full;
      break;
    case 2:
      hand.strength = (max_no_card == 4) ? HandStrength::Four : HandStrength::Full;
      break;
    case 3:
      hand.strength = (max_no_card == 3) ? HandStrength::Three : HandStrength::Two;
      break;
    case 4:
      hand.strength = HandStrength::One;
      break;
    default:
      hand.strength = HandStrength::High;
      break;
    };

    constexpr int64_t value_mutiplier{ 100 };
    int64_t overall_val{ static_cast<int64_t>(hand.strength) };
    for (auto card : hand.cards) {
        overall_val = (overall_val * value_mutiplier + static_cast<int64_t>(card)); 
    }
    hand.overall_value = overall_val;
  }

  std::sort(hands.begin(), hands.end(), [](const Hand &hand1, const Hand &hand2) {
    return hand1.overall_value > hand2.overall_value;
  });

  int rank{ 1 };
  for (auto iter = hands.rbegin(); iter != hands.rend(); ++iter, rank++) { (*iter).rank = rank; }
}

// void rank_hands(Hands &hands)
// {
//   if (hands.empty()) { return; }

//   std::sort(hands.begin(), hands.end(), [](const Hand &hand1, const Hand &hand2) {
//     if (hand1.strength != hand2.strength) { return false; }// don't alter the sorting by strength
//     return hand1.overall_value > hand2.overall_value;
//   });

//   int rank{ 1 };
//   for (auto iter = hands.rbegin(); iter != hands.rend(); ++iter, rank++) { (*iter).rank = rank; }
// }

int64_t calculate_winnings(const Hands &hands)
{
  if (hands.empty()) { return 0; }

  int64_t total_winnings{};
  for (const auto &hand : hands) {
    total_winnings += static_cast<int64_t>(hand.bid) * static_cast<int64_t>(hand.rank);
  }
  return total_winnings;
}