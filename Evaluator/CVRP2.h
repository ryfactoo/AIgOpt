#ifndef ALG_OPT_CVRP2_H
#define ALG_OPT_CVRP2_H

#include <boost/multi_array.hpp>
#include "IEvaluator.h"

class CVRP2 final : public IEvaluator {
private:
    int capacity;
    boost::multi_array<int, 2> distanceMatrix;
    std::vector<int> demands;
public:
    CVRP2(std::string &instanceName,
         const std::vector<std::pair<int, int>> &coords,
         const std::vector<int> &demands,
         int capacity);

    [[nodiscard]] int getCapacity() const;

    [[nodiscard]] int evaluate(const std::vector<int> &genotype) const override;

    int getDistance(int cityA, int cityB);

    int getDemand(int city);
};

#endif //ALG_OPT_CVRP2_H
