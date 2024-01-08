#pragma once

#include <string>

#include <AofCode_Cpp/aoc_library.hpp>

namespace AofCode_Cpp::cmake {
inline constexpr std::string_view campaign_year = "2023";
inline constexpr std::string_view campaign_day = "day07";
}// namespace AofCode_Cpp::cmake

enum class FaceCard { T = 10, J, Q, K, A };
enum HandStrength {High, One, Two, Three, Full, Four, Five };

using Cards = std::vector<int>;

struct Hand
{
  Cards cards{};
  int bid{};
  HandStrength strength{ HandStrength::High };
  int rank{};
  int winnings{};
};

using Hands = std::vector<Hand>;

/**
 * @brief given a set of hand strings create an unorderd Hand vector
 *
 * @param hands_data a series of strings containing the hand information
 * @return Hands
 *
 * @note The cards in the hand are sorted in descending value.
 */
Hands build_hands(const AoCLib::line_data &hands_data);

/**
 * @brief order the cards by stength from strongest to weakest;
 *
 * @param hands
 */
void order_hands_by_strength(Hands &hands);

/**
 * @brief Rank the hands by standard poker rules.  The hands must be previously
 * sorted into bid order.
 *
 * @param hands
 */
void rank_hands(Hands &hands);

/**
 * @brief use the Jacks as Jokers to strengthen the hands but reset their value to 1
 * 
 * @param hands 
 */
void strengthen_hands(Hands &hands);
