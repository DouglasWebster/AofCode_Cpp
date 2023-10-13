#pragma once

#include <map>
#include <string>

#include <AofCode_Cpp/aoc_library.hpp>

namespace AofCode_Cpp::cmake {
inline constexpr std::string_view campaign_year = "2022";
inline constexpr std::string_view campaign_day = "day22";
}// namespace AofCode_Cpp::cmake

enum class Direction { right = 0, down = 1, left = 2, up = 3 };

enum class Rotation { right = 'R', left = 'L', terminate = 'T' };

using Board = std::vector<std::string>;
using Move = std::pair<int, Rotation>;
using Moves = std::vector<Move>;
using Location = std::pair<std::pair<int, int>, Direction>;

/**
 * @brief   converts the last row of the raw_data to a Moves vector
 *
 * @param raw_data - A vector of vector of char.  This is non constant as the routine removes the
 * last two rows.
 * @return Moves -  a vector of pairs of the form <move_amount, which way to turn>
 *
 * @note   The input data always ends with a move_amount.  In order to create a
 *          valid final move 'T' (Terminate!) is added to the last move pair.
 */
Moves strip_off_moves(AoCLib::char_data &raw_data);

/**
 * @brief create a square board from the map of the board supplied.
 *
 * @param board_data the data for the board.  Note: it must have the moves removed before calling.
 * @return Board a square board with extra squares marked with ' '.
 *
 * @note The map of the board should have the two terminating rows (a void row and the row of
 * movement data) stripped of before calling.
 */
Board make_game_board(const AoCLib::char_data &board_data);

/**
 * @brief Get the start position on the password board
 *
 * @param board - the board to scan
 * @return Location - the start position of the board,  This is in board positions starting at {0,
 * 0}
 *
 * @note The start position is the leftmost open tile of the top row of tiles.
 *       Initially, you are facing to the right
 */
Location get_start_position(const Board &board);

/**
 * @brief create a string consisting of the tiles of either the row or column on which the move
 * occurs
 *
 * @param Board - The board from which to extract the string
 * @param direction the direction in which the movement will occur.
 * @return std::string - a string representing the single row or column required.
 *
 * @note If the movement direction is up or right the board is string is reversed so all movement
 * can occur left to right
 */
std::string extract_movement_tiles(const Board &board, const Location &location);

/**
 * @brief makes one move for the password
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
int make_move(const Board &board, const Move &move_to, Location current_location);

/**
 * @brief update the location i.e where we are and where we are facing.
 *
 * @param offset - the position on either the x or y axis
 * @param move - gives which way we need to turn; either left or right.
 * @param location Where we started from and which way we were facing.
 */
void update_location(int offset, const Move &move, Location &location);

using Tile = std::pair<int, int>;
using Face = std::vector<Tile>;
using MapCube = std::vector<Face>;
using FaceLinks = std::map<int, int>;

FaceLInks initialise_face_links();

MapCube initialise_map_cube(const Board & board);

int create_map_cube(const Board &board, MapCube &map_cube, FaceLInks &face_links);
