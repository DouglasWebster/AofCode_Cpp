#include <algorithm>
#include <limits>
#include <map>
#include <numeric>
#include <queue>

#include "2023_day20.hpp"

Messages Module::do_flip_flop(const Signal &signal)
{
  if (signal.second == Level::High) { return {}; }

  std::vector<Identity> identities{};
  for (const auto &output : this->outputs) { identities.push_back(output.first); }

  if (this->state == State::On) {
    this->state = State::Off;
    this->low_pulses += identities.size();
    return { this->index, Level::Low, identities };
  }
  this->state = State::On;
  this->high_pulses += identities.size();
  return { this->index, Level::High, identities };
}

Messages Module::do_conjunction(const Signal &signal)
{

  auto [input, level] = signal;
  for (auto &connection : this->inputs) {
    if (input.second == connection.first.second) { connection.second = level; }
  }

  Level output_level{ Level::Low };
  for (const auto &mod_input : this->inputs) {
    if (mod_input.second == Level::Low) {
      output_level = Level::High;
      break;
    }
  }
  std::vector<Identity> identities{};
  for (const auto &output : this->outputs) { identities.push_back(output.first); }

  auto pulses{ identities.size() };
  if (output_level == Level::High) {
    this->high_pulses += pulses;
  } else {
    this->low_pulses += pulses;
  }

  return { this->index, output_level, identities };
}

Messages Module::do_signal(const Signal &signal)
{

  if (this->type == ModuleType::NoType) { return Messages{}; }
  if (this->type == ModuleType::FlipFlop) { return do_flip_flop(signal); }
  if (this->type == ModuleType::Conjunction) { return do_conjunction(signal); }

  std::vector<Identity> identities{};
  // default to a Button or Broadcaster so just send a low to all outputs.
  for (const auto &output : outputs) {
    identities.push_back(output.first);
    ++this->low_pulses;
  }
  return Messages{ this->index, Level::Low, identities };
}

Modules build_modules(const AoCLib::line_data &data)
{
  if (data.empty()) { return {}; }

  Modules modules{};
  Module button{};
  button.type = ModuleType::Button;
  button.name = "button";
  Connection broadcaster{};
  broadcaster.first.first = "broadcaster";
  button.outputs.emplace_back(broadcaster);
  modules.emplace_back(button);

  for (const auto &line : data) {
    Module module{};
    auto sections{ AoCLib::split_string_at_delimter(line, ' ') };
    if (sections[0][0] == 'b') {
      module.type = ModuleType::Broadcaster;
      module.name = sections[0];
    } else {
      module.type = (sections[0][0] == '%') ? ModuleType::FlipFlop : ModuleType::Conjunction;
      module.name = sections[0].substr(1);
    }
    auto section_iter = sections.begin() + 2;
    while (section_iter != sections.end()) {
      while ((*section_iter).back() == ' ' || (*section_iter).back() == ',') {
        (*section_iter).pop_back();
      }
      Connection new_connection{};
      new_connection.first.first = *section_iter;
      module.outputs.emplace_back(new_connection);
      ++section_iter;
    }


    modules.emplace_back(module);
  }

  std::map<std::string, size_t> links{};
  size_t index{};
  for (auto &module : modules) {
    module.index = index;
    links.emplace(module.name, index);
    ++index;
  }

  // link the outputs to the respective module index
  // and create the inputs on the recieving modules
  for (auto &module : modules) {
    for (auto &output : module.outputs) {
      auto module_name{ output.first.first };
      auto link = links.find(module_name);
      if (link
          == links.end()) {// an unknown output so create a NoType module at the end of the modules.
        Module new_module{};
        new_module.name = module_name;
        new_module.index = modules.size();
        new_module.type = ModuleType::NoType;
        links.emplace(new_module.name, new_module.index);

        modules.emplace_back(new_module);
        output.first.second = new_module.index;
      } else {
        output.first.second = link->second;
      }
      auto [name, location] = output.first;
      modules[location].add_input(module.name, module.index);
    }
  }

  return modules;
}

Feeds get_rx_grandparents(const Modules &modules)
{
  if (modules.empty()) { return {}; }

  size_t rx_parent{};

  for (const auto &module : modules) {
    if (module.name == "rx") {
      rx_parent = module.inputs.front().first.second;
      break;
    }
  }

  Feeds feeds{};

  const auto grandparents{ modules[rx_parent].inputs };
  for (const auto &input : grandparents) { feeds.emplace(input.first.second, 0); }

  return feeds;
}

size_t fire_rx(Modules &modules, Feeds &feeds)
{
  if (modules.empty() || feeds.empty()) { return 0; }

  constexpr auto max_iters{ std::numeric_limits<size_t>::max() };

  size_t rx_parent{};

  for (const auto &module : modules) {
    if (module.name == "rx") {
      rx_parent = module.inputs.front().first.second;
      break;
    }
  }


  for (size_t push{ 1 }; push < max_iters; ++push) {// put a limit on the iterations;

    std::queue<Messages> message_queue{};
    message_queue.push(modules[0].do_signal(Signal{}));

    while (!message_queue.empty()) {
      auto next_message{ message_queue.front() };
      message_queue.pop();

      auto source_mod_index{ std::get<0>(next_message) };
      auto next_mod{ std::get<2>(next_message).front().second };
      auto signal_level{ std::get<1>(next_message) };

      if (next_mod == rx_parent && signal_level == Level::High) {
        // account for it cycling more than once before the others cycle once
        feeds[source_mod_index] = push - feeds[source_mod_index];
      }

      auto source_level{ std::get<1>(next_message) };
      auto sinks{ std::get<2>(next_message) };
      for (const auto &sink : sinks) {
        const Signal signal{ Identity("", source_mod_index), source_level };
        const auto reply{ modules[sink.second].do_signal(signal) };
        if (!std::get<2>(reply).empty()) { message_queue.push(reply); }
      }
    }

    if (std::none_of(
          feeds.begin(), feeds.end(), [](const auto &feed) { return feed.second == 0; })) {
      for (const auto &feed : feeds) {
        const auto &[index, count] = feed;
        std::cout << modules[index].name << " cycles " << count << " times\n";
      }
      return std::accumulate(feeds.begin(), feeds.end(), 1ULL, [](auto x, const auto &item) {
        return std::lcm(x, item.second);
      });
    }
  }

  return max_iters;
}
