#pragma once

#include <string>

#include <AofCode_Cpp/aoc_library.hpp>
#include <map>
#include <vector>

namespace AofCode_Cpp::cmake {
    inline constexpr std::string_view campaign_year = "2023";
    inline constexpr std::string_view campaign_day = "day04";
} //namespace AofCode::cmake

using CardNumbers = std::vector<int>;
using CardCopies = std::vector<int>;

/**
 * @brief a map contining a vector of winning numbers referenced by card
 */
using WinningsNumberMap = std::map<int, CardNumbers>;

/**
 * @brief a map contining a vector of the card numbers referenced by card
 */
using CardNumberMap = std::map<int, CardNumbers>;

/**
 * @brief record the number of cards to copy and the winning points;
*/
using Winnings = std::pair<int, int>;

/**
 * @brief given a list of scratchcard data create two maps, each indexed by card number. 
 * One contining the list of winning numbers, the other containin a list of numbers to check
 *
 * @param card_data a list of scratchcard data
 * @param winning_numbers_map contians the numbers to check against
 * @param card_numbers_map contains the numbers to check
 */

void convert_raw_data_to_maps(const AoCLib::line_data &card_data,
  WinningsNumberMap &winning_numbers_map,
  CardNumberMap &card_numbers_map);

/**
 * @brief calculate the winning point for a scratchcard
 * 
 * @param winners the winning numbers for the scratchcard
 * @param numbers the scratchcard numbers to check
 * @return int the total points the card is worth
 */
Winnings calculate_card_winnings(const CardNumbers &winners, const CardNumbers &numbers);

/**
 * @brief add in the extra cards won by the scratchcards
 * 
 * @param current_card the current card number.
 * @param card_copies a vector holding the current count of each card's copies 
 * @param cards_won the amount of copies the current card has won.
 */
void inflate_card_copies(int current_card, CardCopies &card_copies, int cards_won);
