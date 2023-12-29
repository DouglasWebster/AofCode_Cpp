#include <chrono>
#include <iostream>
#include <numeric>
#include <queue>

#include "2023_day20.hpp"

int main()
{
  auto time_start = std::chrono::high_resolution_clock::now();

  std::string data_file = CURRENT_LIST_DIR;
  data_file += "/input.txt";

  const AoCLib::line_data puzzle_data{ AoCLib::vectorise_line_data(data_file) };

  if (puzzle_data.empty()) {
    std::cout << "No data to analyse!  Terminating program.";
    return 0;
  }

  constexpr int total_runs{ 1000 };

  auto machine{ build_modules(puzzle_data) };

  for (int run{}; run < total_runs; ++run) {
    std::queue<Messages> message_queue{};

    message_queue.push(machine[0].do_signal(Signal{}));

    while (!message_queue.empty()) {
      auto next_message{ message_queue.front() };
      message_queue.pop();

      auto source_mod_index{ std::get<0>(next_message) };
      auto source_level{ std::get<1>(next_message) };
      auto sinks{ std::get<2>(next_message) };
      for (const auto &sink : sinks) {
        const Signal signal{ Identity("", source_mod_index), source_level };
        const auto reply{ machine[sink.second].do_signal(signal) };
        if (!std::get<2>(reply).empty()) { message_queue.push(reply); }
      }
    }
  }

  size_t total_low{};
  size_t total_high{};
  for (const auto &module : machine) {
    total_low += module.low_pulses;
    total_high += module.high_pulses;
  }

  machine.clear();
  machine = build_modules(puzzle_data);

  Feeds feeds{get_rx_grandparents(machine)};
  const auto total_count{fire_rx(machine, feeds)};

  std::cout << "Advent of Code " << AofCode_Cpp::cmake::campaign_year << " "
            << AofCode_Cpp::cmake::campaign_day << '\n';
  std::cout << "Part 1 solution: Product of low and high pulses: " << total_high * total_low
            << "\n";
  std::cout << "Part 2 solution: Pushes needed to fire rx " << total_count << '\n';

  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - time_start);
  std::cout << "Time taken by program: " << duration.count() << " microseconds"
            << "\n";

  return 0;
}
