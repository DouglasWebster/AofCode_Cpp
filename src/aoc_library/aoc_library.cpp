#include <AofCode_Cpp/aoc_library.hpp>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>


std::string removeLeadingSpaces(const std::string &input)
{
  const size_t start = input.find_first_not_of(" \t");// Find the first non-space character

  if (start != std::string::npos) {
    return input.substr(start);// Return the substring starting from the first non-space character
  }

  return "";// If the string is all spaces, return an empty string
}

AoCLib::int_data AoCLib::vectorise_int_data(const std::string &file_name) noexcept
{
  int_data data{};
  if (file_name.empty()) { return data; }

  std::ifstream source_file{ file_name };
  if (!source_file) {
    std::cerr << "AoCLib Error: int data file " << file_name << " could not be opened.\n";
    return data;
  }

  while (source_file && !source_file.eof()) {
    std::string line_read;
    std::getline(source_file, line_read);

    std::stringstream integer_stream(line_read);

    std::vector<int> line_data{};
    int number{};
    while (integer_stream >> number) {
      line_data.push_back(number);
      if (integer_stream.peek() == ',') { integer_stream.ignore(); }
    }

    data.push_back(line_data);
  }

  return data;
}

AoCLib::str_data AoCLib::vectorise_string_data(const std::string &file_name,
  const char delimiter) noexcept
{
  str_data data{};
  if (file_name.empty()) { return data; }

  std::ifstream source_file{ file_name };
  if (!source_file) {
    std::cerr << "AoCLib Error: str data file " << file_name << " could not be opened.\n";
    return data;
  }

  while (source_file && !source_file.eof()) {
    std::string line_read;
    std::vector<std::string> words{};

    std::getline(source_file, line_read);

    std::stringstream word_stream(line_read);

    std::string word;
    while (std::getline(word_stream, word, delimiter)) {
      words.push_back(removeLeadingSpaces(word));
    }

    data.push_back(words);
  }

  return data;
}
AoCLib::char_data AoCLib::vectorise_char_data(const std::string &file_name) noexcept
{
  char_data data{};

  if (file_name.empty()) { return data; }

  std::ifstream source_file{ file_name };
  if (!source_file) {
    std::cerr << "AoCLib Error: char data file " << file_name << " could not be opened.\n";
    return data;
  }

  while (source_file && !source_file.eof()) {
    std::string line_read;
    std::getline(source_file, line_read);

    const std::vector<char> words(line_read.begin(), line_read.end());

    data.push_back(words);
  }

  return data;
}

std::vector<std::string> AoCLib::split_string_into_chunks(const std::string &str, size_t chunk_size)
{
  std::vector<std::string> result;
  for (size_t chunk_start{ 0 }; chunk_start < str.length(); chunk_start += chunk_size) {
    result.push_back(str.substr(chunk_start, chunk_size));
  }

  return result;
}

std::vector<std::string> AoCLib::split_string_at_delimter(const std::string &str, char delimiter)
{
  std::vector<std::string> tokens{};
  std::istringstream tokenStream(str);
  std::string token;

  while (std::getline(tokenStream, token, delimiter)) {

    tokens.push_back(token);
    char next_char{};
    tokenStream.get(next_char);
    while (next_char == ' ' ) {
      tokenStream.get(next_char);
    }
    tokenStream.putback(next_char);
  }

  return tokens;
}
