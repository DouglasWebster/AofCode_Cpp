#pragma once

#include <AofCode_Cpp/aoc_library_export.hpp>

#include <iostream>
#include <utility>
#include <vector>
#include <string>


namespace AoCLib {

using int_data = std::vector<std::vector<int>>;
using str_data = std::vector<std::vector<std::string>>;

/**
 * @brief vectorise each line of the input into a vector of integers.
 * 
 * @param file_name the path to the file containing the raw data
 * @return int_data a std::vector<std::vector<int>>
 * 
 * @note The function returns and empty vector if it is unable to open the file.
 */
[[nodiscard]] int_data vectorise_int_data(const std::string &file_name) noexcept;

/**
 * @brief vectorise each line of the input into a vector of strings.
 * 
 * @param file_name the path to the file containing the raw data
 * @return str_data a std::vector<std::vector<std::string>>
 * 
 * @note The function returns and empty vector if it is unable to open the file.
 */
[[nodiscard]] str_data vectorise_string_data(const std::string &file_name, const char delimiter = ' ') noexcept;


}// namespace AoCLib
