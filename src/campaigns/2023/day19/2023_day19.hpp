#pragma once

#include <string>
#include <list>
#include <limits>
#include <tuple>
#include <list>

#include <AofCode_Cpp/aoc_library.hpp>

namespace AofCode_Cpp::cmake {
    inline constexpr std::string_view campaign_year = "2023";
    inline constexpr std::string_view campaign_day = "day19";
} //namespace AofCode::cmake

struct Part {
    int cool{};
    int musical{};
    int aero{};
    int shiny{};
    bool accepted{false};
    int total {};
};

using Parts = std::vector<Part>;

/**
 * @brief encodes what happended in the operation
 * the first item indicates if the operaton has passed or not.
 * on a pass the rest of the information is not used.
 * A fail indicates that no further operation are to be done
 * and the next item indicates where to go.  If this is size_t::max 
 * then the last item indicates whether the item should be accepted or rejected.
 */
using PassFail = std::tuple<bool, size_t, std::string>;

struct Rule {
    char rating{};
    char operand{};
    int limit{};
    std::string destination{};
    size_t next{std::numeric_limits<size_t>::max()};

    PassFail do_rule(const Part &part ) const ;



};

using Operations = std::list<Rule>;

// then name of the workflow and a vector of operations
using Workflow = std::pair<std::string, Operations>;
using Workflows = std::vector<Workflow>;

Parts create_parts_inventory(const AoCLib::line_data &data);

Workflows create_workflows(const AoCLib::line_data &data);

/**
 * @brief builds the links to the next operations location in the vector
 * 
 * @param workflows 
 * @return size_t the location of the starting point for the machine
 */
size_t build_indexes(Workflows &workflows);

void do_workflows(const Workflows &workflows, Part &part, size_t start);

int accepted_ratings_total(const Parts &parts);

struct RemainingRatingsRange {
    std::pair<int, int> x_left{1, 4000};
    std::pair<int, int> m_left{1, 4000};
    std::pair<int, int> a_left{1, 4000};
    std::pair<int, int> s_left{1, 4000};
};

/**
 * @brief NextWorkflow holds the pointer to the next set of 
 * rules to consider and the remaining ranges avaialble 
 */
using NextWorkflow = std::pair<size_t, RemainingRatingsRange>;
using AcceptedRatings = std::list<RemainingRatingsRange>;

AcceptedRatings get_accepted_ratings(const Workflows &workflows, size_t start);