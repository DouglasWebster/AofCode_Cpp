#pragma once

#include <AofCode_Cpp/aoc_library_export.hpp>

#include <iostream>
#include <utility>
#include <vector>
#include <string>


namespace AoCLib {

using int_data = std::vector<std::vector<int>>;
using str_data = std::vector<std::vector<std::string>>;
using char_data = std::vector<std::vector<char>>;

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
 * @param file_name the path to the file containing the raw data.
 * @param delimiter the character used to determine where to split the line - defaults to a space.
 * @return str_data a std::vector<std::vector<std::string>>
 * 
 * @note The function returns and empty vector if it is unable to open the file.
 */
[[nodiscard]] str_data vectorise_string_data(const std::string &file_name, const char delimiter = ' ') noexcept;

/**
 * @brief vectorise each line of the input into a vector of char.
 * 
 * @param file_name the path to the file containing the raw data.
 * @return str_data a std::vector<std::vector<std::string>>
 * 
 * @note The function returns and empty vector if it is unable to open the file.
 */
[[nodiscard]] char_data vectorise_char_data(const std::string &file_name) noexcept;

/**
 * @brief given a string split it into a vector of string of a given size.
 * 
 * @param str the string to be split
 * @param chunk_size the size of each chunk
 * @return std::vector<std::string> 
 */
std::vector<std::string> split_string_into_chunks(const std::string &str, size_t chunk_size);

/**
 * @brief given a string create a vector of strings using the dilimter as the split poings
 * 
 * @param str the string to split into parts
 * @param delimiter the character where the string is to be split - this is NOT retained.
 * @return std::vector<std::string> 
 */
std::vector<std::string> split_string_at_delimter(const std::string& str, char delimiter);
}// namespace AoCLib
