#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

#include <2023_day08.hpp>

TEST_CASE(" 2023 day07 testing", "[day09]")
{
  std::stringstream tmp_file;
  tmp_file << std::tmpnam(nullptr) << "_2023_day08.txt";// NOLINT: This is not thread safe!

  std::string test_data = "RL\n\n";
  test_data += "AAA = (BBB, CCC)\n";
  test_data += "BBB = (DDD, EEE)\n";
  test_data += "CCC = (ZZZ, GGG)\n";
  test_data += "DDD = (DDD, DDD)\n";
  test_data += "EEE = (EEE, EEE)\n";
  test_data += "GGG = (GGG, GGG)\n";
  test_data += "ZZZ = (ZZZ, ZZZ)";

  std::ofstream test_file{ tmp_file.str() };
  if (!test_file) {
    std::cerr << "Test file " << tmp_file.str() << "could not be opened for writing\n";
  }

  test_file << test_data << std::flush;

  AoCLib::line_data puzzle_test_data{ AoCLib::vectorise_line_data(tmp_file.str()) };

  SECTION("check building of the network and instuctions")
  {
    Instructions instructions = create_instruction(puzzle_test_data);
    Instructions check_instruction{};
    check_instruction.push('R');
    check_instruction.push('L');

    CHECK(check_instruction.front() == 'R');
    CHECK(check_instruction.back() == 'L');

    MoveNetwork move_network{};
    move_network.push_back(Move("AAA", Directions("BBB", "CCC")));

    CHECK(move_network.front().first == "AAA");
    CHECK(move_network.front().second == Directions("BBB", "CCC"));
  }

  SECTION("check movement")
  {

    Instructions instructions = create_instruction(puzzle_test_data);
    Instructions check_instruction{};
    check_instruction.push('R');
    check_instruction.push('L');

    MoveNetwork move_network{};
    move_network.push_back(Move("AAA", Directions("BBB", "CCC")));
    move_network.push_back(Move("BBB", Directions("DDD", "EEE")));
    move_network.push_back(Move("CCC", Directions("ZZZ", "CCC")));
    move_network.push_back(Move("DDD", Directions("DDD", "DDD")));
    move_network.push_back(Move("EEE", Directions("EEE", "EEE")));
    move_network.push_back(Move("EEE", Directions("EEE", "EEE")));
    move_network.push_back(Move("ZZZ", Directions("EEE", "EEE")));

    CHECK(make_move(instructions, move_network, 0) == 2);
    CHECK(instructions.front() == 'L');
  }

  SECTION("check navigate map")
  {


    Instructions check_instruction = create_instruction(puzzle_test_data);
    check_instruction.push('R');
    check_instruction.push('L');

    MoveNetwork move_network{};
    move_network.push_back(Move("AAA", Directions("BBB", "CCC")));
    move_network.push_back(Move("BBB", Directions("DDD", "EEE")));
    move_network.push_back(Move("CCC", Directions("ZZZ", "CCC")));
    move_network.push_back(Move("DDD", Directions("DDD", "DDD")));
    move_network.push_back(Move("EEE", Directions("EEE", "EEE")));
    move_network.push_back(Move("EEE", Directions("EEE", "EEE")));
    move_network.push_back(Move("ZZZ", Directions("EEE", "EEE")));

    CHECK(navigate_map(check_instruction, move_network) == 2);

    check_instruction.pop();
    check_instruction.pop();
    check_instruction.push('L');
    check_instruction.push('L');
    check_instruction.push('R');

    move_network.clear();
    move_network.push_back(Move("AAA", Directions("BBB", "BBB")));
    move_network.push_back(Move("BBB", Directions("AAA", "ZZZ")));
    move_network.push_back(Move("ZZZ", Directions("ZZZ", "ZZZ")));

    CHECK(navigate_map(check_instruction, move_network) == 6);
  }

  // clean up after each test
  std::filesystem::path temp_file_path = tmp_file.str();
  if (std::filesystem::exists(temp_file_path)) { std::filesystem::remove(temp_file_path); }
}

TEST_CASE(" checking part 2", )
{

  std::stringstream tmp_file;
  tmp_file << std::tmpnam(nullptr) << "_2023_day08.txt";// NOLINT: This is not thread safe!

  std::string test_data = "LR\n\n";
  test_data += "11A = (11B, XXX)\n";
  test_data += "11B = (XXX, 11Z)\n";
  test_data += "11Z = (11B, XXX)\n";
  test_data += "22A = (22B, XXX)\n";
  test_data += "22B = (22C, 22C)\n";
  test_data += "22C = (22Z, 22Z)\n";
  test_data += "22Z = (22B, 22B)\n";
  test_data += "XXX = (XXX, XXX)";

  std::ofstream test_file{ tmp_file.str() };
  if (!test_file) {
    std::cerr << "Test file " << tmp_file.str() << "could not be opened for writing\n";
  }

  test_file << test_data << std::flush;

  AoCLib::line_data puzzle_test_data{ AoCLib::vectorise_line_data(tmp_file.str()) };

  SECTION("check generation of starting positions")
  {
    StartPositions starts{ get_start_postions(puzzle_test_data) };

    CHECK_THAT(starts, Catch::Matchers::Equals(StartPositions{ 0, 3 }));
  }

  SECTION("check follow_nodes ") {

    CHECK(follow_nodes(puzzle_test_data) == 6);

  }


  // clean up after each test
  std::filesystem::path temp_file_path = tmp_file.str();
  if (std::filesystem::exists(temp_file_path)) { std::filesystem::remove(temp_file_path); }
}
