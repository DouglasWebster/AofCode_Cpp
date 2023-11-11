#pragma once

#include <string>
#include <memory>

#include <AofCode_Cpp/aoc_library.hpp>

namespace AofCode_Cpp::cmake {
    inline constexpr std::string_view campaign_year = "2022";
    inline constexpr std::string_view campaign_day = "day21";
} //namespace AofCode::cmake



enum class Operators {
    No_Op,
    Subtract,
    Add,
    Divide,
    Multiply
};

struct MonkeyInfo {
    std::string name{};
    size_t location;
    int_fast64_t operand{};
    Operators monkey_op{Operators::No_Op};
    std::string lh_name{};
    std::string rh_name{};
    size_t lh_vector_index {0};
    size_t rh_vector_index {0};
    size_t parent{0};
};

using MonkeyData = std::vector<MonkeyInfo>;

/**
 * @brief build the initial vector of MonkeyInfo information
 * 
 * @param data a vector<vector<string>> of initial data
 * @return MonkeyData a vector of MonkeyInfo
 */
MonkeyData create_data_vector(const AoCLib::str_data &data);

using RootAndHumnIndex = std::pair<size_t, size_t>;

/**
 * @brief fill in the links to the child nodes 
 * 
 * @param monkey_data 
 * 
 * @note The tree is implemented as a vector so the links to the child nodes will be vector indexes.
 */
auto build_tree_links(MonkeyData &monkey_data) -> RootAndHumnIndex;

/**
 * @brief Get the root index object
 * 
 * @param monkey_data 
 * @return int64_t the index where the "root" monkey is located
 */
size_t get_root_index(const MonkeyData &monkey_data);

/**
 * @brief do a recursive calculation staring at "root"
 * 
 * @param monkey_data
 * @param start_index the starting position of the calculation;
 * @return int the value of the calculation from the starting index
 */
int64_t calculate_totals (const MonkeyData & monkey_data, size_t start_index = 0);

using AncestorOperands = std::vector<std::pair<size_t, Operators>>;

/**
 * @brief Get the path from the root to a monkey.
 * 
 * @param monkey_name the name of the monkey whose path we want to find
 * @param monkey_data 
 * @return AncestorPosition  a list of the ancestors from root to the required monkey  
 */
AncestorOperands get_ancestors(std::string_view monkey_name, const MonkeyData &monkey_data);

/**
 * @brief determine the number that has to be balanced
 * 
 * @param monkey_data 
 * @return int64_t - the sum from the opposite branch to the humn branch
 * 
 * @note the function does the following:
 * * get the ancestors of the humn.
 * * determine the side of the root equality that humn is on.
 * * Calculate the sum of the other side of the equation; the sum that has to be balanced. * 
 */
int64_t calculate_sum_to_balance(const MonkeyData & monkey_data);

using PartialSum = std::pair<int64_t, Operators>;
using PartialSums = std::vector<PartialSum>;

/**
 * @brief get the partial sums for list of ancestors
 * 
 * @param monkey_data the full tree of monkeys
 * @param ancestors the list of locations and operators which require the partial sums calculating
 * @return PartialSums - A list of values and the operators
 * 
 * @note 
 * If the penultimate partial sums operator is either a multiplication or a division then value is
 * distributed to itself and the last partial sum i.e  
 * [2, *], [ 3, -] -> [6, -], [3, *]
 */
PartialSums calculate_partial_sums(const MonkeyData &monkey_data, const AncestorOperands &ancestors);

/**
 * @brief determine the value that will terminate the partial sums so that it equals the target;
 * 
 * @param partial_sums a list of operands and operations to perform.
 * @param target the target required
 * @return int64_t the value required.
 */
int64_t calc_humn_value(const PartialSums & partial_sums, int64_t target);
