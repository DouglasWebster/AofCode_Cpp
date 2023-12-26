#include "2023_day19.hpp"
#include <map>
#include <numeric>
#include <stack>

Parts create_parts_inventory(const AoCLib::line_data &data)
{
  if (data.empty()) { return Parts{}; }

  Parts parts{};

  for (const auto &line : data) {
    if (line[0] != '{') { continue; }

    const std::string part_data{ line.substr(1, line.length() - 2) };
    auto ratings{ AoCLib::split_string_at_delimter(part_data, ',') };
    Part part{};
    for (const auto &rating : ratings) {
      const char type{ rating.front() };
      const int value{ std::stoi(rating.substr(2)) };
      switch (type) {
      case 'x':
        part.cool = value;
        break;
      case 'm':
        part.musical = value;
        break;
      case 'a':
        part.aero = value;
        break;
      case 's':
        part.shiny = value;
        break;
      default:
        break;
      }
    }
    part.total = part.cool + part.musical + part.aero + part.shiny;
    parts.push_back(part);
  }
  return parts;
}

Workflows create_workflows(const AoCLib::line_data &data)
{
  if (data.empty()) { return Workflows{}; }

  Workflows workflows{};

  for (const auto &line : data) {
    if (line.empty()) { break; }

    Workflow workflow{};
    auto workflow_parts{ AoCLib::split_string_at_delimter(line, '{') };

    workflow.first = workflow_parts.front();
    workflow_parts.back().pop_back();
    Operations operations{};

    const auto operation_details{ AoCLib::split_string_at_delimter(workflow_parts.back(), ',') };

    for (const auto &detail : operation_details) {
      Rule operation{};
      if (detail.length() == 1) {
        operation.destination = detail;
        operations.push_back(operation);
        continue;
      }

      if (detail[1] != '<' && detail[1] != '>') {
        operation.destination = detail;
        operations.push_back(operation);
        continue;
      }

      const auto detail_parts{ AoCLib::split_string_at_delimter(detail, ':') };
      operation.rating = detail[0];
      operation.operand = detail[1];
      operation.limit = std::stoi(detail_parts.front().substr(2));
      operation.destination = detail_parts.back();
      operations.push_back(operation);
    }
    workflow.second = operations;
    workflows.push_back(workflow);
  }

  return workflows;
}

size_t build_indexes(Workflows &workflows)
{
  if (workflows.empty()) { return std::numeric_limits<size_t>::max(); }

  std::map<std::string, size_t> links{};
  size_t index{};
  size_t in_location{};

  for (const auto &workflow : workflows) {
    links.emplace(workflow.first, index);
    if (workflow.first == "in") { in_location = index; }
    ++index;
  }

  for (auto &workflow : workflows) {
    for (auto &operation : workflow.second) {
      if (operation.destination != "A" && operation.destination != "R") {
        operation.next = links[operation.destination];
      }
    }
  }

  return in_location;
}

void do_workflows(const Workflows &workflows, Part &part, size_t start)
{
  Workflow workflow(workflows[start]);
  bool finished{ false };
  while (!finished) {
    for (const auto &operation : workflow.second) {
      PassFail pass_fail{ operation.do_rule(part) };
      if (!std::get<0>(pass_fail)) {
        if (std::get<1>(pass_fail) == std::numeric_limits<size_t>::max()) {
          part.accepted = (std::get<2>(pass_fail) == "A");
          finished = true;
          break;
        }
        workflow = workflows[std::get<1>(pass_fail)];
        break;
      }
    }
  }
}

int accepted_ratings_total(const Parts &parts)
{
  return std::accumulate(parts.begin(), parts.end(), 0, [](int x, auto part) {
    return x + ((part.accepted) ? part.total : 0);
  });
}

// NOLINTBEGIN (readability-function-cognitive-complexity)
bool apply_rule(RemainingRatingsRange &ranges, char rating, char operand, int limit)
{
  bool range_change{ false };

  switch (rating) {
  case 'x':
    if (operand == '>') {
      if (limit < ranges.x_left.first) { break; }
      range_change = true;
      ranges.x_left.first = limit + 1;
      break;
    }
    if (limit > ranges.x_left.second) { break; }
    range_change = true;
    ranges.x_left.second = limit - 1;
    break;
  case 'm':
    if (operand == '>') {
      if (limit < ranges.m_left.first) { break; }
      range_change = true;
      ranges.m_left.first = limit + 1;
      break;
    }
    if (limit > ranges.m_left.second) { break; }
    range_change = true;
    ranges.m_left.second = limit - 1;
    break;
  case 'a':
    if (operand == '>') {
      if (limit < ranges.a_left.first) { break; }
      range_change = true;
      ranges.a_left.first = limit + 1;
      break;
    }
    if (limit > ranges.a_left.second) { break; }
    range_change = true;
    ranges.a_left.second = limit - 1;
    break;
  case 's':
    if (operand == '>') {
      if (limit < ranges.s_left.first) { break; }
      range_change = true;
      ranges.s_left.first = limit + 1;
      break;
    }
    if (limit > ranges.s_left.second) { break; }
    range_change = true;
    ranges.s_left.second = limit - 1;
    break;
  default:
    break;
  }
  return range_change;
}

AcceptedRatings get_accepted_ratings(const Workflows &workflows, size_t start)
{
  if (workflows.empty()) { return AcceptedRatings{}; }

  std::stack<NextWorkflow> next_rule_set{};
  const Workflow &starting_worksflow{ workflows[start] };

  AcceptedRatings accepted_ratings{};

  // start with the first workflow and apply the full rating to each rule.
  // Prime the stack with the exit conditions for each rule.
  RemainingRatingsRange start_ranges{};
  for (const auto &rule : starting_worksflow.second) {
    RemainingRatingsRange next_ranges{ start_ranges };

    const size_t link{ rule.next };

    if (rule.operand != 0) {
      apply_rule(start_ranges, rule.rating, rule.operand, rule.limit);
      auto operand = (rule.operand == '<') ? '>' : '<';
      int correction = (rule.operand == '<') ? -1 : 1;
      apply_rule(next_ranges, rule.rating, operand, rule.limit + correction);
    }
    if (rule.destination[0] == 'A') {
      accepted_ratings.emplace_front(start_ranges);

      continue;
    }

    next_rule_set.emplace(link, start_ranges);
    start_ranges = next_ranges;
  }

  while (!next_rule_set.empty()) {
    NextWorkflow next_rule{ next_rule_set.top() };
    next_rule_set.pop();
    Workflow workflow{ workflows[next_rule.first] };

    RemainingRatingsRange ranges{ next_rule.second };
    for (const auto &rule : workflow.second) {
      RemainingRatingsRange to_store_ranges{ ranges };

      if (rule.operand != 0) {// ammend the range for the next op
        auto operand = (rule.operand == '<') ? '>' : '<';
        int correction = (rule.operand == '<') ? -1 : 1;
        apply_rule(ranges, rule.rating, operand, rule.limit + correction);
      }

      if (rule.destination[0] < 'Z') {// immeditate rejection or acceptance .
        if( rule.destination[0] =='A' ) { // acceptance so this is a viable passing range
          apply_rule(to_store_ranges, rule.rating, rule.operand, rule.limit );
          accepted_ratings.emplace_front(to_store_ranges);
        }
        continue;
      }

      const size_t link{ rule.next }; // a new worksflow so store it's position and the ranges it will work on
      if (rule.operand != 0) {
        apply_rule(to_store_ranges, rule.rating, rule.operand, rule.limit);
      }
      next_rule_set.emplace(link, to_store_ranges);
    }
  }
  return accepted_ratings;
}
// NOLINTEND (readability-function-cognitive-complexity)

PassFail Rule::do_rule(const Part &part) const
{
  PassFail pass_fail{ true, next, destination };// assume it passes

  int value{};

  switch (rating) {
  case 'a':
    value = part.aero;
    break;
  case 'x':
    value = part.cool;
    break;
  case 'm':
    value = part.musical;
    break;
  case 's':
    value = part.shiny;
    break;
  default:
    break;
  }

  if (operand == 0) { std::get<0>(pass_fail) = false; }
  if (operand == '>' && value > limit) { std::get<0>(pass_fail) = false; }
  if (operand == '<' && value < limit) { std::get<0>(pass_fail) = false; }

  return pass_fail;
}
