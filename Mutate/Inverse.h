#ifndef ALG_OPT_INVERSE_H
#define ALG_OPT_INVERSE_H


#include <random>
#include "IMutate.h"

class Inverse : public IMutate {
private:
    std::mt19937 rng;
    std::uniform_int_distribution<> firstDist;
    std::uniform_int_distribution<> secondDist;
public:
    explicit Inverse(int genotypeSize);
    void mutate(std::vector<int> &genotype) override;
};


#endif //ALG_OPT_INVERSE_H
