#pragma once

#include <string>

#include <AofCode_Cpp/aoc_library.hpp>

namespace AofCode_Cpp::cmake {
    inline constexpr std::string_view campaign_year = "2023";
    inline constexpr std::string_view campaign_day = "day09";
} //namespace AofCode::cmake

using Sequence = std::vector<int64_t>;
using History = std::vector<Sequence>;
using Tree = std::vector<History>;

/**
 * @brief given a sequence build a the histories until the history is all zero's
 * 
 * @param sequence a vector of ints
 * @return History
 */
History build_history(const Sequence &sequence);

/**
 * @brief given a tree add the next value to the end of each sequence.  The 
 * next value is given by the sum of the last value in this sequence + the
 * last value in the next sequence.
 * 
 * @param history 
 */
void extrapolate_next_value(History & history);

/**
 * @brief calculate the sum of the last item from the first history in the tree. 
 * 
 * @param tree
 * @return int64_t 
 */
int64_t calculate_extrapolated_sum(const Tree & tree);