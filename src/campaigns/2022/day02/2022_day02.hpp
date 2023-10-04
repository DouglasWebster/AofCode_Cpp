#pragma once

#include <string>

#include <AofCode_Cpp/aoc_library.hpp>

namespace AofCode_Cpp::cmake {
inline constexpr std::string_view campaign_year = "2022";
inline constexpr std::string_view campaign_day = "day02";
}// namespace AofCode_Cpp::cmake

using strategy = std::vector<std::pair<std::string, std::string>>;

strategy collate_moves(const AoCLib::str_data &);
int first_strategy(const std::pair<std::string, std::string> &);
int second_strategy(const std::pair<std::string, std::string> &);

