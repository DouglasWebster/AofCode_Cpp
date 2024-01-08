#include "2023_day07.hpp"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>


void dump_hands(const Hands &hands)
{
  std::string data_file = CURRENT_LIST_DIR;
  data_file += "/card_dump.txt";

  std::ofstream card_dump;
  card_dump.open(data_file, std::ofstream::out | std::ofstream::trunc);

  for (const auto &hand : hands) {
    card_dump << "Strength " << hand.strength;
    card_dump << ", Cards: ";
    for (auto card : hand.cards) { card_dump << std::setw(3) << card; }

    card_dump << ", Bid: " << std::setw(4) << hand.bid;
    card_dump << ", Rank: " << std::setw(5) << hand.rank;// NOLINT
    card_dump << ", Winnings: " << std::setw(7) << hand.winnings << '\n';// NOLINT
  }
  card_dump.close();
}

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
    const Hand hand{ cards, stoi(details[1]) };

    hands.push_back(hand);
  }
  return hands;
}

void order_hands_by_strength(Hands &hands)
{
  if (hands.empty()) { return; }

  for (auto &hand : hands) {
    std::map<int, int> card_count;
    std::pair<std::map<int, int>::iterator, bool> ret;
    for (auto card : hand.cards) {
      ret = card_count.insert(std::pair(card, 1));
      if (!ret.second) { ret.first->second += 1; }
    }

    // int max_no_card{};
    // for (const auto &item : card_count) {
    //   if (item.second > max_no_card) { max_no_card = item.second; }
    // }

    const int max_no_card = (*std::max_element(card_count.begin(), card_count.end(), [](const auto &item_1, const auto &item_2) {
      return item_1.second < item_2.second;
    })).second;

    switch (card_count.size()) {
    case 1:
      hand.strength = HandStrength::Five;
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
    case 5:// NOLINT
      hand.strength = HandStrength::High;
      break;
    default:
      break;
    };

    std::stable_sort(hands.begin(), hands.end(), [](const Hand &hand1, const Hand &hand2) {
      return hand1.strength > hand2.strength;
    });
  }
}

bool compare_hands(const Hand &hand1, const Hand &hand2)
{
  for (size_t index{}; index < hand1.cards.size(); ++index) {
    const int hand1_val{ hand1.cards[index] };
    const int hand2_val{ hand2.cards[index] };
    if (hand1_val == hand2_val) { continue; }
    return hand1_val > hand2_val;
  }
  return false;
}

void rank_hands(Hands &hands)
{
  if (hands.empty()) { return; }

  std::stable_sort(hands.begin(), hands.end(), [](const Hand &hand1, const Hand &hand2) {
    if (hand1.strength != hand2.strength) { return false; }
    for (size_t index{}; index < hand1.cards.size(); ++index) {
      const int hand1_val{ hand1.cards[index] };
      const int hand2_val{ hand2.cards[index] };
      if (hand1_val == hand2_val) { continue; }
      return hand1_val > hand2_val;
    }
    return false;
  });


  int rank{ 1 };
  for (auto iter = hands.rbegin(); iter != hands.rend(); ++iter, rank++) {
    (*iter).rank = rank;
    (*iter).winnings = (*iter).bid * rank;
  }
}

// NOLINTBEGIN (readability-function-cognitive-complexity)
void strengthen_hands(Hands &hands)
{
  constexpr int Jack{ 11 };
  constexpr int Joker{ 1 };
  constexpr int Five{ 5 };
  constexpr int Four{ 4 };
  constexpr int Three{ 3 };
  constexpr int Two{ 2 };
  constexpr int One{ 1 };
  constexpr int Zero(0);

  for (auto &hand : hands) {
    for (auto &card : hand.cards) {
      if (card == Jack) { card = Joker; }
    }
  }

  for (auto &hand : hands) {
    int jokers{};
    std::map<int, int> card_count;
    std::pair<std::map<int, int>::iterator, bool> ret;
    for (auto card : hand.cards) {
      if (card == Joker) {
        ++jokers;  // don't add the jokers to the list of cards, just keep track of how many.
        continue;
      }
      ret = card_count.insert(std::pair(card, 1));
      if (!ret.second) { ret.first->second += 1; }
    }

    int max_no_card{};
    for (const auto &item : card_count) {
      if (item.second > max_no_card) { max_no_card = item.second; }
    }

    max_no_card += jokers;
    switch (card_count.size()) {
    case Zero:
    [[]] case One:
      hand.strength = HandStrength::Five;
      break;
    case Two:
      hand.strength = (max_no_card == 4) ? HandStrength::Four : HandStrength::Full;
      break;
    case Three:
      hand.strength = (max_no_card == 3) ? HandStrength::Three : HandStrength::Two;
      break;
    case Four:
      hand.strength = HandStrength::One;
      break;
    case Five:
      hand.strength = HandStrength::High;
      break;
    default:
      break;
    };

    std::stable_sort(hands.begin(), hands.end(), [](const Hand &hand1, const Hand &hand2) {
      return hand1.strength > hand2.strength;
    });
  }
}
// NOLINTEND (readability-function-cognitive-complexity)