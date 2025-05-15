#ifndef ALG_OPT_TABUSEARCH_H
#define ALG_OPT_TABUSEARCH_H

#include "IMetaheuristic.h"
#include "TabuSearch/TabuList.h"
#include "NeighbourhoodGen/INeighbours.h"
#include "Util/PopulationStats.h"


class TabuSearch final : public IMetaheuristic {
private:
    TabuList tabu; // container for forbidden genotypes
    std::unique_ptr<INeighbours> neighbourGen; // strategy for creating new solutions
    std::vector<Solution> neighbourhood; // new solutions
    Solution best; // best solution found in whole run
    Solution current; // current point of search
    unsigned int _iterations; // iterations of alg
    PopulationStats logger; // stat logging for alg run
    bool enableLogging; // is logging enabled
public:
    TabuSearch(
            const IEvaluator &problem,
            int iterations,
            int tabuSize,
            std::unique_ptr<INeighbours> neighbourGen,
            Solution& initialSolution,
            bool enableLogging = false
    );

    [[nodiscard]] const Solution &getBestSolution() const override;

    [[nodiscard]] int getIterations() const;

    void setIterations(int iterations);

    void run() override;

    void dumpLogs(std::ostream &os) override;
};


#endif //ALG_OPT_TABUSEARCH_H
