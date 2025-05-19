#ifndef ALG_OPT_POPULATIONSTATS_H
#define ALG_OPT_POPULATIONSTATS_H

#include <vector>
#include "Solution/Solution.h"
#include "csv.hpp"
#include <climits>

// min max avg std current
using Stats = std::tuple<int, int, double, double, int>;

class PopulationStats {
private:
    std::vector<Stats> allStats;
public:
    void ratePopulation(std::vector<Solution> &population, int currentScore = INT_MAX) {
        auto& stats = allStats.emplace_back(INT_MAX, INT_MIN, 0., 0., currentScore);
        for (const auto &sol: population) {
            auto score = sol.getScore();
            std::get<0>(stats) = std::min(std::get<0>(stats), score);  // min
            std::get<1>(stats) = std::max(std::get<1>(stats), score);  // max
            std::get<2>(stats) += score;
        }
        std::get<2>(stats) /= population.size();
        for (const auto &sol: population) {
            auto scoreMinusAvg = sol.getScore() - std::get<2>(stats);
            std::get<3>(stats) += scoreMinusAvg * scoreMinusAvg;
        }
        std::get<3>(stats) = sqrt(std::get<3>(stats));
    }

    void reserve(int n) {
        allStats.reserve(n);
    }

    static void writeHeaders(std::ostream &os) {
        os << "min,max,avg,std,current\n";
    }

    void dump(std::ostream &os) {
        auto writer = csv::make_csv_writer(os);
        csv::set_decimal_places(2);
        for (auto& stats: allStats) {
            writer << stats;
        }
        writer.flush();
    }
};

#endif //ALG_OPT_POPULATIONSTATS_H
