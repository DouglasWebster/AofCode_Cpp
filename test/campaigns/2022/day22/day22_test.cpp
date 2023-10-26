#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include <filesystem>
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


  constexpr auto up = static_cast<size_t>(Direction::up); // NOLINT
  constexpr auto right = static_cast<size_t>(Direction::right);
  constexpr auto down = static_cast<size_t>(Direction::down);
  constexpr auto left = static_cast<size_t>(Direction::left);

  FaceLinks test_links{initialise_face_directions(4)};
  FaceLinks problem_links{initialise_face_directions()};

  SECTION(" check face links are set up correctly")
  {
    CHECK(test_links.size() == 7);  // don't forget to count the dummy zero'th face!
    CHECK(test_links[1][up] == std::make_pair(face_2, Direction::down));
    CHECK(test_links[2][down] == std::make_pair(face_5, Direction::up));
    CHECK(test_links[3][right] == std::make_pair(face_4, Direction::right));
    CHECK(test_links[4][left] == std::make_pair(face_3, Direction::left));
    CHECK(test_links[5][right] != std::make_pair(face_2, Direction::down));
    CHECK(test_links[6][up] == std::make_pair(face_4, Direction::left));

    CHECK(problem_links.size() == 7);  // don't forget to count the dummy zero'th face!
    CHECK(problem_links[1][up] == std::make_pair(face_6, Direction::right));
    CHECK(problem_links[2][down] == std::make_pair(face_3, Direction::left));
    CHECK(problem_links[3][right] == std::make_pair(face_2, Direction::up));
    CHECK(problem_links[4][left] == std::make_pair(face_1, Direction::right));
    CHECK(problem_links[5][right] != std::make_pair(face_3, Direction::up));
    CHECK(problem_links[6][up] == std::make_pair(face_4, Direction::up));
  }

  SECTION("check transitions for the test cube")
  {
    SECTION(" check correct cell and heading on same direction face transitions")
    {

      TileDirection current_tile{ { 1, { 3, 1 } }, Direction::down };
      TileDirection test_destination_tile{ { 4, { 0, 1 } }, Direction::down };
      TileDirection next_tile = determine_cell_on_face_change(test_links, current_tile, 4);
      CHECK(next_tile == test_destination_tile);

      current_tile = TileDirection{ { 4, { 0, 2 } }, Direction::up };
      test_destination_tile = TileDirection{ { 1, { 3, 2 } }, Direction::up };
      next_tile = determine_cell_on_face_change(test_links, current_tile, 4);
      CHECK(next_tile == test_destination_tile);

      current_tile = TileDirection{ { 3, { 3, 3 } }, Direction::right };
      test_destination_tile = TileDirection{ { 4, { 3, 0 } }, Direction::right };
      next_tile = determine_cell_on_face_change(test_links, current_tile, 4);
      CHECK(next_tile == test_destination_tile);

      current_tile = TileDirection{ { 6, { 3, 0 } }, Direction::left };
      test_destination_tile = TileDirection{ { 5, { 3, 3 } }, Direction::left };
      next_tile = determine_cell_on_face_change(test_links, current_tile, 4);
      CHECK(next_tile == test_destination_tile);
    }

    SECTION(" check correct cell and heading on reverse direction face transitions")
    {
      // note, there are no left to right transitions.

      TileDirection current_tile{ { 2, { 3, 1 } }, Direction::down };
      TileDirection test_destination_tile{ { 5, { 3, 2 } }, Direction::up };
      TileDirection next_tile = determine_cell_on_face_change(test_links, current_tile, 4);
      CHECK(next_tile == test_destination_tile);


      current_tile = TileDirection{ { 1, { 0, 2 } }, Direction::up };
      test_destination_tile = TileDirection{ { 2, { 0, 1 } }, Direction::down };
      next_tile = determine_cell_on_face_change(test_links, current_tile, 4);
      CHECK(next_tile == test_destination_tile);

      current_tile = TileDirection{ { 6, { 3, 3 } }, Direction::right };
      test_destination_tile = TileDirection{ { 1, { 0, 3 } }, Direction::left };
      next_tile = determine_cell_on_face_change(test_links, current_tile, 4);
      CHECK(next_tile == test_destination_tile);
    }

    SECTION(" check correct cell and heading on twisting face transitions")
    {
      TileDirection current_tile{ { 1, { 1, 0 } }, Direction::left };
      TileDirection test_destination_tile{ { 3, { 0, 1 } }, Direction::down };
      TileDirection next_tile = determine_cell_on_face_change(test_links, current_tile, 4);
      CHECK(next_tile == test_destination_tile);

      current_tile = TileDirection{ { 2, { 2, 0 } }, Direction::left };
      test_destination_tile = TileDirection{ { 6, { 3, 1 } }, Direction::up };
      next_tile = determine_cell_on_face_change(test_links, current_tile, 4);
      CHECK(next_tile == test_destination_tile);

      current_tile = TileDirection{ { 4, { 3, 3 } }, Direction::right };
      test_destination_tile = TileDirection{ { 6, { 0, 0 } }, Direction::down };
      next_tile = determine_cell_on_face_change(test_links, current_tile, 4);
      CHECK(next_tile == test_destination_tile);

      current_tile = TileDirection{ { 6, { 0, 1 } }, Direction::up };
      test_destination_tile = TileDirection{ { 4, { 2, 3 } }, Direction::left };
      next_tile = determine_cell_on_face_change(test_links, current_tile, 4);
      CHECK(next_tile == test_destination_tile);

      current_tile = TileDirection{ { 3, { 0, 1 } }, Direction::up };
      test_destination_tile = TileDirection{ { 1, { 1, 0 } }, Direction::right };
      next_tile = determine_cell_on_face_change(test_links, current_tile, 4);
      CHECK(next_tile == test_destination_tile);

      current_tile = TileDirection{ { 3, { 3, 1 } }, Direction::down };
      test_destination_tile = TileDirection{ { 5, { 2, 0 } }, Direction::right };
      next_tile = determine_cell_on_face_change(test_links, current_tile, 4);
      CHECK(next_tile == test_destination_tile);
    }
  }

  SECTION("check transitions for the problem cube")
  {
    TileDirection current_tile{};
    TileDirection destination_tile{};

    SECTION("Face 1")
    {
      current_tile = TileDirection{ { 1, { 1, 49 } }, Direction::right };
      destination_tile = TileDirection{ { 2, { 1, 0 } }, Direction::right };
      CHECK(determine_cell_on_face_change(problem_links, current_tile, 50) == destination_tile);

      current_tile = TileDirection{ { 1, { 49, 24 } }, Direction::down };
      destination_tile = TileDirection{ { 3, { 0, 24 } }, Direction::down };
      CHECK(determine_cell_on_face_change(problem_links, current_tile, 50) == destination_tile);

      current_tile = TileDirection{ { 1, { 25, 0 } }, Direction::left };
      destination_tile = TileDirection{ { 4, { 24, 0 } }, Direction::right };
      CHECK(determine_cell_on_face_change(problem_links, current_tile, 50) == destination_tile);

      current_tile = TileDirection{ { 1, { 0, 25 } }, Direction::up };
      destination_tile = TileDirection{ { 6, { 25, 0 } }, Direction::right };
      CHECK(determine_cell_on_face_change(problem_links, current_tile, 50) == destination_tile);
    }

    SECTION("Face 2")
    {
      current_tile = TileDirection{ { 2, { 0, 49 } }, Direction::right };
      destination_tile = TileDirection{ { 5, { 49, 49 } }, Direction::left };
      CHECK(determine_cell_on_face_change(problem_links, current_tile, 50) == destination_tile);

      current_tile = TileDirection{ { 2, { 49, 15 } }, Direction::down };
      destination_tile = TileDirection{ { 3, { 15, 49 } }, Direction::left };
      CHECK(determine_cell_on_face_change(problem_links, current_tile, 50) == destination_tile);

      current_tile = TileDirection{ { 2, { 25, 0 } }, Direction::left };
      destination_tile = TileDirection{ { 1, { 25, 49 } }, Direction::left };
      CHECK(determine_cell_on_face_change(problem_links, current_tile, 50) == destination_tile);

      current_tile = TileDirection{ { 2, { 0, 25 } }, Direction::up };
      destination_tile = TileDirection{ { 6, { 49, 25 } }, Direction::up };
      CHECK(determine_cell_on_face_change(problem_links, current_tile, 50) == destination_tile);
    }

    SECTION("Face 3")
    {
      current_tile = TileDirection{ { 3, { 25, 49 } }, Direction::right };
      destination_tile = TileDirection{ { 2, { 49, 25 } }, Direction::up };
      CHECK(determine_cell_on_face_change(problem_links, current_tile, 50) == destination_tile);

      current_tile = TileDirection{ { 3, { 49, 30 } }, Direction::down };
      destination_tile = TileDirection{ { 5, { 0, 30 } }, Direction::down };
      CHECK(determine_cell_on_face_change(problem_links, current_tile, 50) == destination_tile);

      current_tile = TileDirection{ { 3, { 25, 0 } }, Direction::left };
      destination_tile = TileDirection{ { 4, { 0, 25 } }, Direction::down };
      CHECK(determine_cell_on_face_change(problem_links, current_tile, 50) == destination_tile);

      current_tile = TileDirection{ { 3, { 0, 25 } }, Direction::up };
      destination_tile = TileDirection{ { 1, { 49, 25 } }, Direction::up };
      CHECK(determine_cell_on_face_change(problem_links, current_tile, 50) == destination_tile);
    }
    SECTION("Face 4")
    {
      current_tile = TileDirection{ { 4, { 18, 49 } }, Direction::right };
      destination_tile = TileDirection{ { 5, { 18, 0 } }, Direction::right };
      CHECK(determine_cell_on_face_change(problem_links, current_tile, 50) == destination_tile);

      current_tile = TileDirection{ { 4, { 49, 30 } }, Direction::down };
      destination_tile = TileDirection{ { 6, { 0, 30 } }, Direction::down };
      CHECK(determine_cell_on_face_change(problem_links, current_tile, 50) == destination_tile);

      current_tile = TileDirection{ { 4, { 25, 0 } }, Direction::left };
      destination_tile = TileDirection{ { 1, { 24, 0 } }, Direction::right };
      CHECK(determine_cell_on_face_change(problem_links, current_tile, 50) == destination_tile);

      current_tile = TileDirection{ { 4, { 0, 25 } }, Direction::up };
      destination_tile = TileDirection{ { 3, { 25, 0 } }, Direction::right };
      CHECK(determine_cell_on_face_change(problem_links, current_tile, 50) == destination_tile);
    }

    SECTION("Face 5")
    {
      current_tile = TileDirection{ { 5, { 25, 49 } }, Direction::right };
      destination_tile = TileDirection{ { 2, { 24, 49 } }, Direction::left };
      CHECK(determine_cell_on_face_change(problem_links, current_tile, 50) == destination_tile);

      current_tile = TileDirection{ { 5, { 49, 30 } }, Direction::down };
      destination_tile = TileDirection{ { 6, { 30, 49 } }, Direction::left };
      CHECK(determine_cell_on_face_change(problem_links, current_tile, 50) == destination_tile);

      current_tile = TileDirection{ { 5, { 25, 0 } }, Direction::left };
      destination_tile = TileDirection{ { 4, { 25, 49 } }, Direction::left };
      CHECK(determine_cell_on_face_change(problem_links, current_tile, 50) == destination_tile);

      current_tile = TileDirection{ { 5, { 0, 25 } }, Direction::up };
      destination_tile = TileDirection{ { 3, { 49, 25 } }, Direction::up };
      CHECK(determine_cell_on_face_change(problem_links, current_tile, 50) == destination_tile);
    }

    SECTION("Face 6")
    {

      current_tile = TileDirection{ { 6, { 25, 49 } }, Direction::right };
      destination_tile = TileDirection{ { 5, { 49, 25 } }, Direction::up };
      CHECK(determine_cell_on_face_change(problem_links, current_tile, 50) == destination_tile);

      current_tile = TileDirection{ { 6, { 49, 30 } }, Direction::down };
      destination_tile = TileDirection{ { 2, { 0, 30 } }, Direction::down };
      CHECK(determine_cell_on_face_change(problem_links, current_tile, 50) == destination_tile);

      current_tile = TileDirection{ { 6, { 25, 0 } }, Direction::left };
      destination_tile = TileDirection{ { 1, { 0, 25 } }, Direction::down };
      CHECK(determine_cell_on_face_change(problem_links, current_tile, 50) == destination_tile);

      current_tile = TileDirection{ { 6, { 0, 25 } }, Direction::up };
      destination_tile = TileDirection{ { 4, { 49, 25 } }, Direction::up };
      CHECK(determine_cell_on_face_change(problem_links, current_tile, 50) == destination_tile);
    }
  }

  SECTION(" check the face origins map correctly")
  {
    FaceOrigins result{ determine_face_origins(test_board, 4) };

    CHECK(result.size() == 6);

    CHECK(result[1] == std::make_pair(0, 8));
    CHECK(result[2] == std::make_pair(4, 0));
    CHECK(result[3] == std::make_pair(4, 4));
    CHECK(result[4] == std::make_pair(4, 8));
    CHECK(result[5] == std::make_pair(8, 8));
    CHECK(result[6] == std::make_pair(8, 12));

    // now do it with the puzzle data

    std::string puzzle_data_str{
      "/mnt/DEV/cpp_work/AofCode_Cpp/src/campaigns/2022/day22/input.txt"
    };

    AoCLib::char_data puzzle_test_data{ AoCLib::vectorise_char_data(puzzle_data_str) };
    puzzle_test_data.pop_back();
    puzzle_test_data.pop_back();

    Board puzzle_board{ make_game_board(puzzle_test_data) };

    FaceOrigins puzzle_results{ determine_face_origins(puzzle_board) };

    CHECK(puzzle_results.size() == 6);

    CHECK(puzzle_results[1] == std::make_pair(0, 50));
    CHECK(puzzle_results[2] == std::make_pair(0, 100));
    CHECK(puzzle_results[3] == std::make_pair(50, 50));
    CHECK(puzzle_results[4] == std::make_pair(100, 0));
    CHECK(puzzle_results[5] == std::make_pair(100, 50));
    CHECK(puzzle_results[6] == std::make_pair(150, 0));
  }

  SECTION(" check the MapCube has the correct size")
  {
    MapCube result{ initialise_map_cube(test_board, 4) };

    CHECK(result.size() == 6);
    CHECK(result[0].size() == 4);
    CHECK(result[0][0].size() == 4);

    // now do it with the puzzle data

    std::string puzzle_data_str{
      "/mnt/DEV/cpp_work/AofCode_Cpp/src/campaigns/2022/day22/input.txt"
    };

    AoCLib::char_data puzzle_test_data{ AoCLib::vectorise_char_data(puzzle_data_str) };
    puzzle_test_data.pop_back();
    puzzle_test_data.pop_back();

    Board puzzle_board{ make_game_board(puzzle_test_data) };

    MapCube puzzle_cube{ initialise_map_cube(puzzle_board, 50) };

    CHECK(puzzle_cube.size() == 6);
    CHECK(puzzle_cube[0].size() == 50);
    CHECK(puzzle_cube[0][0].size() == 50);

    CHECK(puzzle_cube[0][0][0] == '.');
    CHECK(puzzle_cube[0][25][0] == '#');
    CHECK(puzzle_cube[1][0][47] == '#');
    CHECK(puzzle_cube[1][49][0] == '.');
    CHECK(puzzle_cube[2][3][0] == '#');
    CHECK(puzzle_cube[2][49][2] == '#');
    CHECK(puzzle_cube[5][0][6] == '.');
    CHECK(puzzle_cube[5][49][49] == '.');
  }

  SECTION(" check that moves occur correctly")
  {
    MapCube map_cube{ initialise_map_cube(test_board, 4) };
    TileDirection current_tile{ { 4, { 1, 3 } }, Direction::right };
    TileDirection next_tile{ { 6, { 0, 2 } }, Direction::down };

    CHECK(make_3d_move(map_cube, current_tile, test_links) == true);
    CHECK(current_tile == next_tile);

    current_tile = TileDirection{ { 5, { 3, 2 } }, Direction::down };
    next_tile = TileDirection{ { 2, { 3, 1 } }, Direction::up };

    CHECK(make_3d_move(map_cube, current_tile, test_links) == true);
    CHECK(current_tile == next_tile);

    current_tile = TileDirection{ { 3, { 0, 2 } }, Direction::up };
    next_tile = current_tile;

    CHECK(make_3d_move(map_cube, current_tile, test_links) == false);
    CHECK(current_tile == next_tile);
  }

  SECTION("check move sequence ")
  {
    Moves moves{ { 10, Rotation::right },
      { 5, Rotation::left },
      { 5, Rotation::right },
      { 10, Rotation::left },
      { 4, Rotation::right },
      { 5, Rotation::left },
      { 5, Rotation::terminate } };

    MapCube map_cube{ initialise_map_cube(test_board, 4) };

    TileDirection final_position{ do_3d_moves(moves, map_cube, test_links) };

    CHECK(final_position.first.first == 3);
    CHECK(final_position.first.second.first == 0);
    CHECK(final_position.first.second.second == 2);
    CHECK(final_position.second == Direction::up);
  }

  SECTION(" check password generation")
  {
    FaceOrigins face_origins{ determine_face_origins(test_board, 4) };
    TileDirection final_tile{ { 3, { 0, 2 } }, Direction::up };

    CHECK(calculate_3d_password(final_tile, face_origins) == 5031);
  }
}
