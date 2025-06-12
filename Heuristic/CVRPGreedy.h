#ifndef ALG_OPT_CVRPGREEDY_H
#define ALG_OPT_CVRPGREEDY_H

#include "Solution/Solution.h"
#include "Evaluator/CVRP2.h"

Solution cvrp_greedy(CVRP2 &instance) {
    std::vector<bool> visited((instance.getGenotypeSize() + 3) / 2, false);
    int currentCity = 0, usedCapacity = 0, totalDistance = 0, citiesLeft = visited.size() - 1;
    std::vector<int> genotype;
    genotype.push_back(0);
    while (citiesLeft > 0) {
        int nextCity = 0, nextCityDistance = INT_MAX;
        for (int potentialCity = 1; potentialCity < visited.size(); ++potentialCity) {
            if (visited[potentialCity] || usedCapacity + instance.getDemand(potentialCity) > instance.getCapacity())
                continue;
            if (instance.getDistance(currentCity, potentialCity) < nextCityDistance) {
                nextCityDistance = instance.getDistance(currentCity, potentialCity);
                nextCity = potentialCity;
            }
        }
        if (nextCity == 0) {
            totalDistance += instance.getDistance(currentCity, 0);
            currentCity = 0;
            usedCapacity = 0;
        } else {
            visited[nextCity] = true;
            totalDistance += nextCityDistance;
            usedCapacity += instance.getDemand(nextCity);
            currentCity = nextCity;
            citiesLeft--;
        }
        genotype.push_back(nextCity);
    }
    genotype.push_back(0);
    return {std::move(genotype), totalDistance, nullptr};
}

#endif //ALG_OPT_CVRPGREEDY_H
