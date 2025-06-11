#ifndef ALG_OPT_CVRPGREEDY_H
#define ALG_OPT_CVRPGREEDY_H

#include "Solution/Solution.h"
#include "Evaluator/CVRP.h"

Solution cvrp_greedy(CVRP& instance) {
    std::vector<bool> visited(instance.getGenotypeSize(), false);
    int currentCity = 0;
    visited[currentCity] = true;
    std::vector<int> genotype;
}

#endif //ALG_OPT_CVRPGREEDY_H
