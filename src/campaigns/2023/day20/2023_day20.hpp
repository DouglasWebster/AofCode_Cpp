#pragma once

#include <string>
#include <tuple>
#include <map>

#include <AofCode_Cpp/aoc_library.hpp>

namespace AofCode_Cpp::cmake {
inline constexpr std::string_view campaign_year = "2023";
inline constexpr std::string_view campaign_day = "day20";
}// namespace AofCode_Cpp::cmake

enum class State {
    On,
    Off
};

enum class Level {
    High,
    Low
};

// pair<identity name, modules location>
using Identity = std::pair<std::string, size_t>;
// A Pulse is low (false), high (true);
using Pulse = std::pair<Identity, Level>;
// high(true) or low (false)
using Connection = std::pair<Identity, Level>;
using Signal = std::pair<Identity, Level>;
using Inputs = std::vector<Connection>;
using Outputs = std::vector<Connection>;

// sorce module, output level & sink modules
using Messages = std::tuple<size_t, Level, std::vector<Identity>>;

// high(true) or low (false)
enum class ModuleType {
    FlipFlop,
    Conjunction,
    Broadcaster,
    Button,
    NoType
};

struct Module {
    std::string name{};
    size_t index{};
    Inputs inputs{};
    Outputs outputs{};
    State state{State::Off};
    size_t low_pulses{};
    size_t high_pulses{};
    ModuleType type{ModuleType::NoType};

    Messages do_flip_flop(const Signal &signal);
    Messages do_conjunction(const Signal &signal);

    Messages do_signal(const Signal &signal);
    void add_input(const std::string & connection_name, size_t location) {
        this->inputs.push_back(Connection{{connection_name, location}, Level::Low});
    }
};

using Modules = std::vector<Module>;

Modules build_modules(const AoCLib::line_data & data);

// The feeds are the location of the 4 inputs to &gh (see input.svg)
// These all need to be high to fire rx
// We also keep a count of how many button pushes are needed to fire each feed.
using Feeds = std::map<size_t, size_t>;

Feeds get_rx_grandparents(const Modules &modules);

/**
 * @brief Knowing the feed then we can determine then cycle time to each feed firing.
 * Knowing these individual times then the pushes required to fire rx should be the
 * lowest common multiple of these cycle times
 * 
 * @param modules 
 * @param feeds 
 * @return size_t the button pushes needed to fire rx.
 */
size_t fire_rx(Modules &modules, Feeds &feeds);




