#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include <iostream>

#include <2023_day01.hpp>

// start with a test case that does nothing but fail.

TEST_CASE(" 2023 day01 part 1", "[day01]")
{
    std::vector<std::string> test_data{"1abc2", "pqr3stu8vwx", "a1b2c3d4e5f", "treb7uchet"};

    CHECK(first_digit("") == -1);
    CHECK(last_digit("") == -1);
    CHECK(first_digit("abcdef") == -1);
    CHECK(last_digit ("XYZghe")== -1);
    CHECK(last_digit(test_data[0]) == 2);
    CHECK(first_digit(test_data[1]) == 3);
    CHECK(first_digit(test_data[3]) == last_digit(test_data[3]));

    const int first_line_total = first_digit(test_data[0]) * 10 + last_digit(test_data[0]);
    const int second_line_total = first_digit(test_data[1]) * 10 + last_digit(test_data[1]);
    const int third_line_total = first_digit(test_data[2]) * 10 + last_digit(test_data[2]);
    const int forth_line_total = first_digit(test_data[3]) * 10 + last_digit(test_data[3]);

    CHECK(first_line_total == 12);
    CHECK(second_line_total == 38);
    CHECK(third_line_total == 15);
    CHECK(forth_line_total == 77);
}

TEST_CASE(" 2023 day01 part 2", "[day01]") {
    std::vector<std::string> test_data{"two1nine", "eightwothree", "abcone2threexyz", "xtwone3four", "4nineeightseven2", "zoneight234", "7pqrstsixteen"};

    CHECK(first_number(test_data[0]) == 2);
    CHECK(first_number(test_data[3]) == 2);
    CHECK(first_number(test_data[4])== 4);
    CHECK(last_number(test_data[0]) == 9);
    CHECK(last_number(test_data[2]) == 3);
    CHECK(last_number(test_data[5]) == 4);

    const int first_line_total = first_number(test_data[0]) * 10 + last_number(test_data[0]);
    const int second_line_total = first_number(test_data[1]) * 10 + last_number(test_data[1]);
    const int third_line_total = first_number(test_data[2]) * 10 + last_number(test_data[2]);
    const int forth_line_total = first_number(test_data[3]) * 10 + last_number(test_data[3]);
    const int fifth_line_total = first_number(test_data[4]) * 10 + last_number(test_data[4]);
    const int sixth_line_total = first_number(test_data[5]) * 10 + last_number(test_data[5]);
    const int seventh_line_total = first_number(test_data[6]) * 10 + last_number(test_data[6]);

    CHECK(first_line_total == 29);
    CHECK(second_line_total == 83);
    CHECK(third_line_total == 13);
    CHECK(forth_line_total == 24);
    CHECK(fifth_line_total == 42);
    CHECK(sixth_line_total == 14);
    CHECK(seventh_line_total == 76);


}
