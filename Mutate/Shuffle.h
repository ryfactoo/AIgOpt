#ifndef ALG_OPT_SHUFFLE_H
#define ALG_OPT_SHUFFLE_H


#include <random>
#include "IMutate.h"

class Shuffle : public IMutate {
private:
    std::mt19937 rng;
    std::uniform_int_distribution<> firstDist;
    std::uniform_int_distribution<> secondDist;
public:
    explicit Shuffle(int genotypeSize);

    void mutate(std::vector<int> &genotype) override;
};


#endif //ALG_OPT_SHUFFLE_H
