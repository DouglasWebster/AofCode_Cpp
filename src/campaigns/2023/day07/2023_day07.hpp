#pragma once

#include <string>

#include <AofCode_Cpp/aoc_library.hpp>

namespace AofCode_Cpp::cmake {
    inline constexpr std::string_view campaign_year = "2023";
    inline constexpr std::string_view campaign_day = "day07";
} //namespace AofCode::cmake

enum class FaceCard { T = 10, J, Q, K, A };
enum HandStrength {
    High,
    One,
    Two,
    Three,
    Full,
    Four,
    Five
};

using Cards = std::vector<int>;

struct Hand {
    Cards cards{};
    int bid{};
    HandStrength strength{HandStrength::High};
    int rank{};
    int64_t overall_value{};
};

using Hands = std::vector<Hand>;

/**
 * @brief given a set of hand strings create an unorderd Hand vector 
 * 
 * @param hand_data a series of strings containing the hand information
 * @return Hands 
 * 
 * @note The cards in the hand are sorted in descending value.
 */
Hands build_hands(const AoCLib::line_data & hands_data);

 /**
  * @brief order the cards by stength from strongest to weakest;
  * 
  * @param hands 
  */
void order_hands_by_bid(Hands &hands);

// /**
//  * @brief Rank the hands by standard poker rules.  The hands must be previously
//  * sorted into bid order.
//  * 
//  * @param Hands 
//  */
// void rank_hands(Hands & hands);

/**
 * @brief calulate the total winning for the hands.
 * 
 * @param hand 
 * @return int64_t 
 */
int64_t calculate_winnings(const Hands &hands);