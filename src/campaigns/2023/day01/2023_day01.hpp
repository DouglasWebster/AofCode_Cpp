#pragma once

#include <string>

#include <AofCode_Cpp/aoc_library.hpp>

namespace AofCode_Cpp::cmake {
    inline constexpr std::string_view campaign_year = "2023";
    inline constexpr std::string_view campaign_day = "day01";
} //namespace AofCode::cmake

/**
 * @brief get the first digit in the data string
 * 
 * @param data the string of characters to inspect
 * @return int the value of the first digit in the data string or -1 on failure to find a digit
 */
int first_digit(std::string_view data);

/**
 * @brief get the last digit in the data string.
 * 
 * @param data the string of characters to inspect
 * @return int the value of the last digit in the data string or -1 on failure to find a digit
 */
int last_digit(std::string_view data);

/**
 * @brief gets the value of the first number in a string.  The number can be either a digit or a word
 * 
 * @param data 
 * @return int the value of the first number.
 */
int first_number(std::string_view data);

/**
 * @brief gets the value of the last number in a string.  The number can be either a digit or a word
 * 
 * @param data 
 * @return int the value of the last number.
 */
int last_number(std::string_view data);

