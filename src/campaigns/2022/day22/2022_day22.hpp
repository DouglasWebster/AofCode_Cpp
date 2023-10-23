#pragma once

#include <map>
#include <string>

#include <AofCode_Cpp/aoc_library.hpp>

namespace AofCode_Cpp::cmake {
inline constexpr std::string_view campaign_year = "2022";
inline constexpr std::string_view campaign_day = "day22";
}// namespace AofCode_Cpp::cmake

constexpr int no_of_faces{ 6 };
constexpr int face_1{ 1 };
constexpr int face_2{ 2 };
constexpr int face_3{ 3 };
constexpr int face_4{ 4 };
constexpr int face_5{ 5 };
constexpr int face_6{ 6 };

enum class Direction { right = 0, down = 1, left = 2, up = 3 };

constexpr int ten{10};

constexpr int face_1_right{ face_1 * ten + static_cast<int>(Direction::right) };
constexpr int face_1_down{ face_1 * ten + static_cast<int>(Direction::down) };
constexpr int face_1_left{ face_1 * ten + static_cast<int>(Direction::left) };
constexpr int face_1_up{ face_1 * ten + static_cast<int>(Direction::up) };

constexpr int face_2_right{ face_2 * ten + static_cast<int>(Direction::right) };
constexpr int face_2_down{ face_2 * ten + static_cast<int>(Direction::down) };
constexpr int face_2_left{ face_2 * ten + static_cast<int>(Direction::left) };
constexpr int face_2_up{ face_2 * ten + static_cast<int>(Direction::up) };

constexpr int face_3_right{ face_3 * ten + static_cast<int>(Direction::right) };
constexpr int face_3_down{ face_3 * ten + static_cast<int>(Direction::down) };
constexpr int face_3_left{ face_3 * ten + static_cast<int>(Direction::left) };
constexpr int face_3_up{ face_3 * ten + static_cast<int>(Direction::up) };

constexpr int face_4_right{ face_4 * ten + static_cast<int>(Direction::right) };
constexpr int face_4_down{ face_4 * ten + static_cast<int>(Direction::down) };
constexpr int face_4_left{ face_4 * ten + static_cast<int>(Direction::left) };
constexpr int face_4_up{ face_4 * ten + static_cast<int>(Direction::up) };

constexpr int face_5_right{ face_5 * ten + static_cast<int>(Direction::right) };
constexpr int face_5_down{ face_5 * ten + static_cast<int>(Direction::down) };
constexpr int face_5_left{ face_5 * ten + static_cast<int>(Direction::left) };
constexpr int face_5_up{ face_5 * ten + static_cast<int>(Direction::up) };

constexpr int face_6_right{ face_6 * ten + static_cast<int>(Direction::right) };
constexpr int face_6_down{ face_6 * ten + static_cast<int>(Direction::down) };
constexpr int face_6_left{ face_6 * ten + static_cast<int>(Direction::left) };
constexpr int face_6_up{ face_6 * ten + static_cast<int>(Direction::up) };

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

using Cell = std::pair<int, int>;
using Tile = std::pair<int, Cell>;
using TileDirection = std::pair<Tile, Direction>;
using Face = std::vector<Tile>;
using MapCube = std::vector<Face>;
using FaceLinks = std::map<int, int>;

/**
 * @brief create the way we are facing when transitioning from one face to another
 *
 * @return FaceLinks A map of face directions.
 */
FaceLinks initialise_face_directions();

/**
 * @brief determine the next cell and direction if changing faces.
 *
 * @param current_tile The current cell location and current face.
 * @param heading Keeps track of the direction **relative** to the cell.
 * @return Tile The face and cell that would be transitioned to,
 */
TileDirection determine_cell_on_face_change(FaceLinks &face_links,
  const TileDirection &current_tile,
  const int face_size);

MapCube initialise_map_cube(const Board &board);

int create_map_cube(const Board &board, MapCube &map_cube, FaceLinks &face_links);
