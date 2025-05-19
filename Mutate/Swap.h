#ifndef ALG_OPT_SWAP_H
#define ALG_OPT_SWAP_H


#include <random>
#include "IMutate.h"

class Swap : public IMutate {
private:
    std::mt19937 rng;
    std::uniform_int_distribution<> firstDist;
    std::uniform_int_distribution<> secondDist;
public:
    explicit Swap(int genotypeSize);
    void mutate(std::vector<int> &genotype) override;
};


#endif //ALG_OPT_SWAP_H
