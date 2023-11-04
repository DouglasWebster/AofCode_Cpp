#pragma once

#include <string>
#include <memory>

#include <AofCode_Cpp/aoc_library.hpp>

namespace AofCode_Cpp::cmake {
    inline constexpr std::string_view campaign_year = "2022";
    inline constexpr std::string_view campaign_day = "day21";
} //namespace AofCode::cmake



enum class Operand {
    No_Op,
    Add,
    Subtract,
    Divide,
    Multiply
};

struct MonkeyInfo {
    std::string name{};
    int value{};
    Operand operand{Operand::No_Op};
    std::string lh_name{};
    std::string rh_name{};
    size_t lh_vector_index {0};
    size_t rh_vector_index {0};
};

using MonkeyData = std::vector<MonkeyInfo>;

/**
 * @brief build the initial vector of MonkeyInfo information
 * 
 * @param data a vector<vector<string>> of initial data
 * @return MonkeyData a vector of MonkeyInfo
 */
auto create_data_vector(const AoCLib::str_data &data) -> MonkeyData;


/**
 * @brief fill in the links to the child nodes 
 * 
 * @param monkey_data 
 * 
 * @note The tree is implemented as a vector so the links to the child nodes will be vector indexes.
 */
auto build_tree_links(MonkeyData &monkey_data) -> void;


/**
 * @brief do a recursive calculation staring at "root"
 * 
 * @param monkey_data
 * @param start_index the starting position of the calculation;
 * @return int the value of the calculation from the starting index
 */
auto calculate_part_1 (const MonkeyData & monkey_data, size_t start_index = 0) -> int;