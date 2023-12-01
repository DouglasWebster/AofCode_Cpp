#include "2023_day01.hpp"

#include <algorithm>
#include <vector>

int first_digit(std::string_view data)
{
  if (data.empty()) { return -1; }

  const size_t first_digit = data.find_first_of("1234567890");
  if (first_digit == std::string::npos) { return -1; }

  return int(data[first_digit]) - '0';
}

int last_digit(std::string_view data)
{

  if (data.empty()) { return -1; }

  const size_t first_digit = data.find_last_of("1234567890");
  if (first_digit == std::string::npos) { return -1; }

  return int(data[first_digit]) - '0';
}

int first_number(std::string_view data)
{
  if (data.empty()) { return -1; }
  const std::vector<std::string> numbers = { "0",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "zero",
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine" };

  size_t first_position{ std::string::npos };
  std::string number{};

  for (const auto &test_str : numbers) {
    const size_t position{ data.find(test_str) };
    if (position < first_position) {
      first_position = position;
      number = test_str;
    }
  }

  if (number.empty()) { return -1; }

  if (number.size() == 1) { return std::stoi(number); }

  for (int offset{ 0 }; const auto &test_str : numbers) {
    if (test_str == number) { return offset - 10; }// NOLINT
    ++offset;
  }

  return -1;
}

int last_number(std::string_view data)
{
  if (data.empty()) { return -1; }

  const std::vector<std::string> numbers = { "0",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "zero",
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine" };

  size_t first_position{ std::string::npos };
  std::string number{};

  for (const auto &test_str : numbers) {
    const size_t position{ data.rfind(test_str) };
    if (position != std::string::npos) {
      if (first_position == std::string::npos) {
        first_position = position;
        number = test_str;
        continue;
      }

      if (position > first_position) {
        first_position = position;
        number = test_str;
      }
    }
  }

  if (number.empty()) { return -1; }

  if (number.size() == 1) { return std::stoi(number); }

  for (int offset{ 0 }; const auto &test_str : numbers) {
    if (test_str == number) { return offset - 10; }// NOLINT
    ++offset;
  }

  return -1;
}
