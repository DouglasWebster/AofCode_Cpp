#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include <iostream>
#include <queue>

#include <2023_day20.hpp>

// start with a test case that does nothing but fail.

TEST_CASE(" 2023 day20 testing", "[day20]")
{
  std::string data_file = CURRENT_LIST_DIR;
  data_file += "/test.txt";

  const AoCLib::line_data puzzle_data{ AoCLib::vectorise_line_data(data_file) };

  SECTION("check building of modules")
  {
    auto modules{ build_modules(puzzle_data) };

    CHECK(modules.size() == 7);
  }

  SECTION("check flip flop operation")
  {
    auto modules{ build_modules(puzzle_data) };

    Signal signal{ Identity{}, Level::Low };

    Module source{ modules[1] };
    auto output = source.do_signal(signal);

    CHECK(std::get<1>(output) == Level::Low);
    CHECK(std::get<2>(output).size() == 1);

    auto sink = modules[std::get<2>(output)[0].second];

    signal = std::make_pair(Identity{ "", std::get<0>(output) }, std::get<1>(output));

    output = sink.do_signal(signal);
    CHECK(sink.state == State::On);
    CHECK(sink.low_pulses == 0);
    CHECK(sink.high_pulses == 2);

    output = sink.do_signal(signal);
    CHECK(sink.state == State::Off);
    CHECK(sink.low_pulses == 2);
    CHECK(sink.high_pulses == 2);
  }

  SECTION("check conjunction operation")
  {
    auto modules{ build_modules(puzzle_data) };
    Signal a_signal{ Identity{ "a", 2 }, Level::High };
    Signal b_signal{ Identity{ "b", 4 }, Level::High };

    Module con{ modules[5] };

    auto output = con.do_signal(a_signal);
    CHECK(std::get<1>(output) == Level::High);
    CHECK(std::get<2>(output)[0].first == "output");

    output = con.do_signal(b_signal);
    CHECK(std::get<1>(output) == Level::Low);
    CHECK(std::get<2>(output)[0].first == "output");
    ;
  }

  SECTION("check machine")
  {
    auto machine{ build_modules(puzzle_data) };

    for (int push{}; push < 1000; ++push) {
      std::queue<Messages> message_queue{};

      message_queue.push(machine[0].do_signal(Signal{}));
      // std::cout << "button push" << push << '\n';

      while (!message_queue.empty()) {
        auto next_message{ message_queue.front() };
        message_queue.pop();

        auto source_mod_index{ std::get<0>(next_message) };
        auto source_level{ std::get<1>(next_message) };
        auto sinks{ std::get<2>(next_message) };
        for (const auto &sink : sinks) {
          const Signal signal{ Identity("", source_mod_index), source_level };
          // std::cout << machine[source_mod_index].name << " - "
          //           << (source_level == Level::Low ? "low" : "high") << " -> "
          //           << machine[sink.second].name << '\n';
          const auto reply{ machine[sink.second].do_signal(signal) };
          if (!std::get<2>(reply).empty()) { message_queue.push(reply); }
        }
      }
      // std::cout << '\n';
    }
    size_t total_low{};
    size_t total_high{};
    for (const auto &module : machine) {
      auto low_pulses{ module.low_pulses };
      auto high_pulses{ module.high_pulses };
      std::cout << "Module " << module.name << " emited " << low_pulses << " low pulses and "
                << high_pulses << " high pulses\n`";
        total_low += low_pulses;
        total_high += high_pulses;
    }

    std::cout << total_low << " low pulses emitted and " << total_high << " high pulses emitted.\n";

    CHECK(total_high * total_low == 11687500);
  }
}
