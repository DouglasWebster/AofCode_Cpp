#pragma once

#include <string>
#include <queue>

#include <AofCode_Cpp/aoc_library.hpp>

namespace AofCode_Cpp::cmake {
    inline constexpr std::string_view campaign_year = "2023";
    inline constexpr std::string_view campaign_day = "day08";
} //namespace AofCode::cmake

using Instructions = std::queue<char>;
using Directions = std::pair<std::string, std::string>;
using Move = std::pair<std::string, Directions>;
using MoveNetwork = std::vector<Move>;

/**
 * @brief Create the instruction object
 * 
 * @param puzzle_data the raw data for the problem 
 * @return Instructions 
 * 
 */
Instructions create_instruction(const AoCLib::line_data &puzzle_data);

/**
 * @brief Create the move_network object
 * 
 * @param move_network the list of nodes for movement
 * @param puzzle_data the raw data for the problem 
 * 
 * @note we create both items at the same time as they are located in the same file.
 */
void create_network(MoveNetwork &move_network, const AoCLib::line_data &puzzle_data); 

/**
 * @brief make a move according to the instructions
 * 
 * @param instructions the list of moves to make
 * @param move_network the list of nodes for movement
 * @param position the current position in the MoveNetwork of moves
 * @param update_instruction - determines whether this function shoud rotate the instruction queue.  
 * Default is to let the function rotate the queue.
 * @return size_t the position in the move_network we arrive at.
 */
size_t make_move(Instructions &instructions, const MoveNetwork &move_network, size_t position, bool update_instruction = true);

/**
 * @brief make moves on the network until it reaches "ZZZ"
 * 
 * @param instructions the movements to make
 * @param move_network the network top traverse
 * @return int the number of steps it takes to reach "ZZZ"
 */
int navigate_map(Instructions & instructions, const MoveNetwork & move_network);

using StartPositions = std::vector<size_t>;

/**
 * @brief Get the start postions object 
 * 
 * @param puzzle_data 
 * @return StartPositions 
 */
StartPositions get_start_postions(const AoCLib::line_data & puzzle_data);

/**
 * @brief given a set of instructions find the steps it takes to finish with
 * all paths on a node ending in Z;
 * 
 * @param puzzle_data 
 * @return int the number of steps
 */
int64_t follow_nodes(const AoCLib::line_data & puzzle_data);