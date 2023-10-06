#include "2022_day04.hpp"
#include <sstream>

Assignments collate_assignments(const AoCLib::str_data &data)
{
  Assignments assignments{};

  if (data.empty()) { return assignments; }

  for (const auto &items : data) {
    if (items.size() != 2) {
      std::cout << "bad data: ";
      for (const auto &item : items) { std::cout << item << ", "; }
      std::cout << "- Ignoring items!\n";
      continue;
    }
    Assignment assignment{};
    Section first_section{};
    std::istringstream first_pair(items[0]);
    std::string number;
    std::getline(first_pair, number, '-');
    first_section.first = std::stoi(number);
    std::getline(first_pair, number, '-');
    first_section.second = std::stoi(number);

    Section second_section{};
    std::istringstream second_pair(items[1]);
    std::getline(second_pair, number, '-');
    second_section.first = std::stoi(number);
    std::getline(second_pair, number, '-');
    second_section.second = std::stoi(number);

    assignment.first = first_section;
    assignment.second = second_section;

    assignments.push_back(assignment);
  }

  return assignments;
}

bool contains_fully(const Assignment &assignment)
{
  if (assignment.first.first <= assignment.second.first) {
    if (assignment.first.second >= assignment.second.second) { return true; }
  }

  if (assignment.second.first <= assignment.first.first) {
    if (assignment.second.second >= assignment.first.second) { return true; }
  }

  return false;
}
