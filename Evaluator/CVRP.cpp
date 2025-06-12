#include "CVRP.h"

CVRP::CVRP(std::string &instanceName, const std::vector<std::pair<int, int>> &coords, const std::vector<int> &demands, int capacity)
        : IEvaluator(demands.size() - 1, instanceName),
          capacity(capacity),
          demands(demands),
          distanceMatrix(boost::extents[coords.size()][coords.size()]) {
    if (coords.size() != demands.size())
        throw std::length_error("coords size doesn't match demands size");
    std::iota(genotypeValues.begin(), genotypeValues.end(), 1);
    for (int i = 0; i < coords.size(); ++i) {
        distanceMatrix[i][i] = 0;
        auto& [xi, yi] = coords[i];
        for (int j = i + 1; j < coords.size(); ++j) {
            auto& [xj, yj] = coords[j];
            int dx = xi - xj;
            int dy = yi - yj;
            int dist = round(sqrt(dx * dx + dy * dy));
            distanceMatrix[i][j] = dist;
            distanceMatrix[j][i] = dist;
        }
    }
}

int CVRP::getDistance(int cityA, int cityB) {
    return distanceMatrix[cityA][cityB];
}

int CVRP::getDemand(int city) {
    return demands[city];
}

int CVRP::getCapacity() const {
    return capacity;
}

int CVRP::evaluate(const std::vector<int> &genotype) const {
    int score = 0;
    int usedCapacity = 0;
    int prevCity = 0;
    for (auto city: genotype) {
        if (usedCapacity + demands[city] <= capacity) {
            score += distanceMatrix[prevCity][city];
            usedCapacity += demands[city];
        } else {
            score += distanceMatrix[prevCity][0] + distanceMatrix[0][city];
            usedCapacity = demands[city];
        }
        prevCity = city;
    }
    score += distanceMatrix[prevCity][0];
    return score;
}

std::vector<int> CVRP::getFenotype(const std::vector<int> &genotype) const {
    std::vector<int> fenotype;
    fenotype.push_back(0);
    int usedCapacity = 0;
    for (auto city: genotype) {
        if (usedCapacity + demands[city] <= capacity) {
            fenotype.push_back(city);
            usedCapacity += demands[city];
        } else {
            fenotype.push_back(0);
            fenotype.push_back(city);
            usedCapacity = demands[city];
        }
    }
    fenotype.push_back(0);
    return fenotype;
}
