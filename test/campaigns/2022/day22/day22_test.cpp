#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <sstream>

#include <2022_day22.hpp>

// start with a test case that does nothing but fail.

TEST_CASE(" Test Part one", "[day22]")
{
  // create a test file for future use.
  std::stringstream tmp_file;
  tmp_file << std::tmpnam(nullptr) << "_2022_day22.txt";// NOLINT: This is not thread safe!
  std::cout << "Temp file name: " << tmp_file.str() << '\n';

  std::string test_data = "        ...#\n";
  test_data += "        .#..\n";
  test_data += "        #...\n";
  test_data += "        ....\n";
  test_data += "...#.......#\n";
  test_data += "........#...\n";
  test_data += "..#....#....\n";
  test_data += "..........#.\n";
  test_data += "        ...#....\n";
  test_data += "        .....#..\n";
  test_data += "        .#......\n";
  test_data += "        ......#.\n";
  test_data += "\n";
  test_data += "10R5L5R10L4R5L5";

  std::cout << test_data << '\n';

  std::ofstream test_file{ tmp_file.str() };
  if (!test_file) {
    std::cerr << "Test file " << tmp_file.str() << "could not be opened for writing\n";
  }
  test_file << test_data << std::flush;

  AoCLib::char_data puzzle_test_data{ AoCLib::vectorise_char_data(tmp_file.str()) };

  Board test_board = {
    ("        ...#    "),
    ("        .#..    "),
    ("        #...    "),
    ("        ....    "),
    ("...#.......#    "),
    ("........#...    "),
    ("..#....#....    "),
    ("..........#.    "),
    ("        ...#...."),
    ("        .....#.."),
    ("        .#......"),
    ("        ......#."),
  };

  SECTION(" strip off the movement data")
  {
    Moves test_moves = { std::make_pair(10, Rotation::right),
      std::make_pair(5, Rotation::left),
      std::make_pair(5, Rotation::right),
      std::make_pair(10, Rotation::left),
      std::make_pair(4, Rotation::right),
      std::make_pair(5, Rotation::left),
      std::make_pair(5, Rotation::terminate) };

    Moves result_moves{ strip_off_moves(puzzle_test_data) };

    CHECK_THAT(result_moves, Catch::Matchers::Equals(test_moves));
  }


  SECTION("  create a rectilinear board from the puzzle data")
  {
    puzzle_test_data.pop_back();
    puzzle_test_data.pop_back();

    Board board{ make_game_board(puzzle_test_data) };

    CHECK_THAT(board, Catch::Matchers::Equals(test_board));
  }

  SECTION(" get start position")
  {

    Location expected_start{ std::make_pair(8, 0), Direction::right };
    Location returned_start{ get_start_position(test_board) };

    CHECK(returned_start == expected_start);
  }

  SECTION(" extract the movement tiles")
  {
    std::string expected_row{ "        ...#    " };

    CHECK(extract_movement_tiles(test_board, Location(std::make_pair(0, 0), Direction::right))
          == expected_row);

    std::reverse(expected_row.begin(), expected_row.end());
    CHECK(extract_movement_tiles(test_board, Location(std::make_pair(0, 0), Direction::left))
          == expected_row);

    std::string expected_column{ "..#..#......" };

    CHECK(extract_movement_tiles(test_board, Location(std::make_pair(8, 0), Direction::down))
          == expected_column);

    std::reverse(expected_column.begin(), expected_column.end());
    CHECK(extract_movement_tiles(test_board, Location(std::make_pair(8, 0), Direction::up))
          == expected_column);
  }

  SECTION(" do movements")
  {

    CHECK(make_move(
            test_board, Move(10, Rotation::right), Location(std::make_pair(8, 0), Direction::right))
          == 10);

    CHECK(make_move(
            test_board, Move(5, Rotation::left), Location(std::make_pair(10, 0), Direction::down))
          == 5);

    CHECK(make_move(
            test_board, Move(5, Rotation::right), Location(std::make_pair(10, 5), Direction::right))
          == 3);

    CHECK(make_move(
            test_board, Move(10, Rotation::left), Location(std::make_pair(3, 5), Direction::down))
          == 7);

    CHECK(make_move(
            test_board, Move(4, Rotation::right), Location(std::make_pair(3, 7), Direction::right))
          == 7);

    CHECK(make_move(
            test_board, Move(5, Rotation::left), Location(std::make_pair(7, 7), Direction::down))
          == 5);

    CHECK(
      make_move(
        test_board, Move(5, Rotation::terminate), Location(std::make_pair(7, 5), Direction::right))
      == 7);

    CHECK(make_move(
            test_board, Move(5, Rotation::terminate), Location(std::make_pair(8, 5), Direction::up))
          == 3);

    CHECK(make_move(
            test_board, Move(9, Rotation::terminate), Location(std::make_pair(8, 1), Direction::up))
          == 6);

    CHECK(
      make_move(
        test_board, Move(12, Rotation::terminate), Location(std::make_pair(9, 7), Direction::left))
      == 11);
  }

  SECTION(" update location")
  {
    Location location{ std::make_pair(8, 0), Direction::right };

    update_location(10, Move(10, Rotation::right), location);
    CHECK(location == Location(std::make_pair(10, 0), Direction::down));

    update_location(5, Move(5, Rotation::left), location);
    CHECK(location == Location(std::make_pair(10, 5), Direction::right));
  }


  // clean up after each test
  std::filesystem::path temp_file_path = tmp_file.str();
  if (std::filesystem::exists(temp_file_path)) { std::filesystem::remove(temp_file_path); }
}

TEST_CASE(" testing part 2", "[day22]")
{
  Board test_board = {
    ("        ...#    "),
    ("        .#..    "),
    ("        #...    "),
    ("        ....    "),
    ("...#.......#    "),
    ("........#...    "),
    ("..#....#....    "),
    ("..........#.    "),
    ("        ...#...."),
    ("        .....#.."),
    ("        .#......"),
    ("        ......#."),
  };

  FaceLinks built_links{ initialise_face_directions() };

  SECTION(" check face links are set up correctly")
  {
    CHECK(built_links.size() == 24);
    CHECK(built_links[face_1_up] == face_2_down);
    CHECK(built_links[face_2_down] == face_5_up);
    CHECK(built_links[face_3_right] == face_4_right);
    CHECK(built_links[face_4_left] == face_3_left);
    CHECK(built_links[face_5_right] != face_2_down);
    CHECK(built_links[face_6_up] == face_4_left);
  }

  SECTION(" check correct cell and heading on same direction face transitions")
  {
    TileDirection current_tile{ { 1, { 3, 1 } }, Direction::down };
    TileDirection destination_tile{ { 4, { 0, 1 } }, Direction::down };
    TileDirection next_tile = determine_cell_on_face_change(built_links, current_tile, 4);
    CHECK(next_tile == destination_tile);

    current_tile = TileDirection{ { 4, { 0, 2 } }, Direction::up };
    destination_tile = TileDirection{ { 1, { 3, 2 } }, Direction::up };
    next_tile = determine_cell_on_face_change(built_links, current_tile, 4);
    CHECK(next_tile == destination_tile);

    current_tile = TileDirection{ { 3, { 3, 3 } }, Direction::right };
    destination_tile = TileDirection{ { 4, { 3, 0 } }, Direction::right };
    next_tile = determine_cell_on_face_change(built_links, current_tile, 4);
    CHECK(next_tile == destination_tile);

    current_tile = TileDirection{ { 6, { 3, 0 } }, Direction::left };
    destination_tile = TileDirection{ { 5, { 3, 3 } }, Direction::left };
    next_tile = determine_cell_on_face_change(built_links, current_tile, 4);
    CHECK(next_tile == destination_tile);
  }

  SECTION(" check correct cell and heading on reverse direction face transitions")
  {
    // note, there are no left to right transitions.

    TileDirection current_tile{ { 2, { 3, 1 } }, Direction::down };
    TileDirection destination_tile{ { 5, { 3, 2 } }, Direction::up };
    TileDirection next_tile = determine_cell_on_face_change(built_links, current_tile, 4);
    CHECK(next_tile == destination_tile);

    current_tile = TileDirection{ { 1, { 0, 2 } }, Direction::up };
    destination_tile = TileDirection{ { 2, { 0, 1 } }, Direction::down };
    next_tile = determine_cell_on_face_change(built_links, current_tile, 4);
    CHECK(next_tile == destination_tile);

    current_tile = TileDirection{ { 6, { 3, 3 } }, Direction::right };
    destination_tile = TileDirection{ { 1, { 0, 3 } }, Direction::left };
    next_tile = determine_cell_on_face_change(built_links, current_tile, 4);
    CHECK(next_tile == destination_tile);
  }

  SECTION(" check correct cell and heading on twisting face transitions")
  {
    TileDirection current_tile{ { 1, { 1, 0 } }, Direction::left };
    TileDirection destination_tile{ { 3, { 0, 1 } }, Direction::down };
    TileDirection next_tile = determine_cell_on_face_change(built_links, current_tile, 4);
    CHECK(next_tile == destination_tile);

    current_tile = TileDirection{ { 2, { 2, 0 } }, Direction::left };
    destination_tile = TileDirection{ { 6, { 3, 1 } }, Direction::up };
    next_tile = determine_cell_on_face_change(built_links, current_tile, 4);
    CHECK(next_tile == destination_tile);

    current_tile = TileDirection{ { 4, { 3, 3 } }, Direction::right };
    destination_tile = TileDirection{ { 6, { 0, 0 } }, Direction::down };
    next_tile = determine_cell_on_face_change(built_links, current_tile, 4);
    CHECK(next_tile == destination_tile);

    current_tile = TileDirection{ { 6, { 0, 1 } }, Direction::up };
    destination_tile = TileDirection{ { 4, { 2, 3 } }, Direction::left };
    next_tile = determine_cell_on_face_change(built_links, current_tile, 4);
    CHECK(next_tile == destination_tile);

    current_tile = TileDirection{ { 3, { 0, 1 } }, Direction::up };
    destination_tile = TileDirection{ { 1, { 1, 0 } }, Direction::right };
    next_tile = determine_cell_on_face_change(built_links, current_tile, 4);
    CHECK(next_tile == destination_tile);

    current_tile = TileDirection{ { 3, { 3, 1 } }, Direction::down };
    destination_tile = TileDirection{ { 5, { 2, 0 } }, Direction::right };
    next_tile = determine_cell_on_face_change(built_links, current_tile, 4);
    CHECK(next_tile == destination_tile);
  }
}
