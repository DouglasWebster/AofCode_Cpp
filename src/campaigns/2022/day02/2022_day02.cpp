#include "2022_day02.hpp"
#include <algorithm>

strategy collate_moves(const AoCLib::str_data &raw_data)
{
  strategy collated_data{};
  collated_data.resize(raw_data.size());

  std::transform(raw_data.begin(), raw_data.end(), collated_data.begin(), [](const auto &move) {
    return std::make_pair(move[0], move[1]);
  });

  return collated_data;
}

enum shape {
  Rock = 'A',
  Paper = 'B',
  Scissors = 'C'
};

constexpr int Rock_loss = 1;
constexpr int Rock_draw = 4;
constexpr int Rock_win = 7;
constexpr int Paper_loss = 2;
constexpr int Paper_draw = 5;
constexpr int Paper_win = 8;
constexpr int Scissors_loss = 3;
constexpr int Scissors_draw = 6;
constexpr int Scissors_win = 9;


int first_strategy(const std::pair<std::string, std::string> &round)
{

  switch (round.first[0]) {
  case Rock: {
    if (round.second == "X") { return Rock_draw; }
    return (round.second == "Y") ? Paper_win : Scissors_loss;
  }
  case Paper: {
    if (round.second == "Y") { return Paper_draw; }
    return (round.second == "Z") ? Scissors_win : Rock_loss;
  }
  case Scissors: {
    if (round.second == "Z") { return Scissors_draw; }
    return (round.second == "X") ? Rock_win : Paper_loss;
    ;
  }
  }

  return 0;
}

int second_strategy(const std::pair<std::string, std::string> & round) { 
  switch (round.first[0]) {
  case Rock: { 
    if (round.second == "X") { return Scissors_loss; }
    return (round.second == "Y") ? Rock_draw : Paper_win;
  }
  case Paper: {
    if (round.second == "X") { return Rock_loss; }
    return (round.second == "Y") ? Paper_draw : Scissors_win;
  }
  case Scissors: {
    if (round.second == "X") { return Paper_loss; }
    return (round.second == "Y") ? Scissors_draw : Rock_win; 
    ;
  }
  }

  return 0;; }
