#pragma once

#include <string>

#include <AofCode_Cpp/aoc_library.hpp>

namespace AofCode_Cpp::cmake {
    inline constexpr std::string_view campaign_year = "2022";
    inline constexpr std::string_view campaign_day = "day22";
} //namespace AofCode::cmake

enum class Direction {
    right,
    down,
    left,
    up
};

enum class Rotation {
    right = 'R',
    left = 'L',
    terminate = 'T'
};

using Board = std::vector<std::string>;
using Move = std::pair<int, Rotation>;
using Moves = std::vector<Move>;
using Location = std::pair<std::pair<int, int>, Direction>;

/**
 * @brief   converts the last row of the raw_data to a Moves vector
 * 
 * @param raw_data A vector of vector of char 
 * @return Moves a vector of pairs of the form <move_amount, which way to turn>
 * 
 * @note   The input data always ends with a move_amount.  In order to create a
 *          valid a 'T' (Terminate!) is added to the last move pair.
 */
Moves strip_off_moves(AoCLib::char_data & raw_data);

/**
 * @brief create a square board from the map of the board supplied.
 * 
 * @param board_data the data for the board.  Note: it must have the moves removed before calling.
 * @return Board a square board with extra squares marked with ' '.
 * 
 * @note The map of the board should have the two terminating rows (a void row and the row of movement
 *          data) stripped of before calling. 
 */
Board make_game_board(const AoCLib::str_data & board_data);


/**
 * @brief makes on move for the password
 * 
 * @param board - the game board for decoding the password
 * @param move_to - the current move to make and how to turn at the end of the move
 * @param current_location the starting postion of the current move.
 * 
 * @return Location - The final position and facing direction at the end of the move. 
 * 
 * @note    All move positions are zero based with {0,0} being the top left of the board.  Password
 *          positions are 1 based {1,1} being the top left of the board.
 */
Location make_move(const Board & board, const Move & move_to, Location current_location);
