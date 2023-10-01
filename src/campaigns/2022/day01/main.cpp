#include <iostream>

#include "2022_day01.hpp"


int main() {
    std::string data_file = CURRENT_LIST_DIR;
    data_file += "/input.txt";

   const AoCLib::int_data raw_vector{AoCLib::vectorise_int_data(data_file)};

    if(raw_vector.empty()) {
        std::cout << "No data to analyse!  Terminating program.";
        return 0;
    }

    const ElvenPacks pack_calories{collate_calories(raw_vector)};
    const ElvenPack pack_totals{sum_calories(pack_calories)};

    std::cout << "Advent of Code " << AofCode_Cpp::cmake::campaign_year << " " << AofCode_Cpp::cmake::campaign_day << '\n';
#if defined(CURRENT_LIST_DIR)
   std::cout << "Puzzle input is at: " << data_file <<'\n';
#endif
    std::cout << "Part 1 solution: " << max_values(pack_totals, 1) << '\n';
    std::cout << "Part 2 solution: " << max_values(pack_totals, 3) << '\n';

    return 0;
}
