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
 * @param board The board from which to extract the string
 * @param location This contains the direction in which the movement will occur.
 * @return std::string - a string representing the single row or column required.
 *
 * @note If the movement direction is up or right the board string is reversed so all movement
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
using MapCube = std::vector<std::vector<std::vector<char>>>; // face -> row -> column -> # or .
using FaceOrigins = std::map<int, Cell>;
using FaceLinks = std::vector<std::vector<std::pair<int, Direction>>>; // Face, Edge -> face, direction 

/**
 * @brief create a vector containing links to the next face of a face transiton.
 * 
 * @param face_size - the size of the face; enables choosing the correct linkage.
 * @return FaceLinks 
 */
FaceLinks initialise_face_directions( const int face_size = 50);

/**
 * @brief determine the next cell and direction if changing faces.
 *
 * @param face_links links to enable a face change if required 
 * @param current_tile The current cell location and current face.
 * @param face_size The number of row/column cells.
 * @return TileDirection The face, cell and direction that would be transitioned to,
 */
TileDirection determine_cell_on_face_change(const FaceLinks &face_links,
  const TileDirection &current_tile,
  const int face_size);

/**
 * @brief determine where the mapping of each faces [0, 0] position to the board location
 * 
 * @param board the vector of strings representing the unfolded cube
 * @param face_size the number of rows/columns of the resulting cube
 * @return FaceOrigins 
 */
FaceOrigins determine_face_origins(const Board &board, const size_t face_size = 50);

/**
 * @brief create a 3d vector representation of the board folded into a cube 
 * 
 * @param board a vector of strings representing the unfolded cube
 * @param face_size the number of row and column elements of a cube face
 * @return MapCube 
 * 
 * @note The board can be considered as containing a number of square sections each face_size
 * square.  The board sections are scanned in a left to right, top to bottom pattern.  A section
 * that contains a ' ' as it's first character is assumed to be a filler section and is
 * discarded.
 */
MapCube initialise_map_cube(const Board &board, const size_t face_size = 50);

/**
 * @brief Do one move on the 3d cube
 * 
 * @param map_cube the cube on which to move
 * @param tile The current location and the direction of movement
 * @param face_links links to enable a face change if required 
 * @return true - the move was successful and the current location has been updated.
 * @return false - the move was blocked and the current location remains the same.
 */
bool make_3d_move(const MapCube &map_cube, TileDirection &tile, const FaceLinks &face_links);

/**
 * @brief complete the moves required.
 * 
 * @param moves the moves required
 * @param map_cube the surface on which the moves occur
 * @param face_links how to reorient the move on a face transition
 * @return TileDirection The final location and direction after the moves complete.
 * 
 * @note The moves are required to have a terminating marker.  If this is not present then the
 * function will return an empty TileDirection.
 */
TileDirection do_3d_moves(const Moves & moves, const MapCube &map_cube, const FaceLinks &face_links );

/**
 * @brief given a tile convert the face, row, column and direction into a password
 * 
 * @param tile the postion tile used to generate the password
 * @param face_origins the mapping of a faces [0, 0] to the board location.
 * @return int the password generated.
 */
int calculate_3d_password( const TileDirection & tile, FaceOrigins & face_origins) ;

