#ifndef ALG_OPT_SWAP_H
#define ALG_OPT_SWAP_H


#include <random>
#include "IMutate.h"

class Swap : public IMutate {
private:
    std::mt19937 rng;
    std::uniform_int_distribution<> dist;
public:
    explicit Swap(int genotypeSize) :
            IMutate(genotypeSize),
            rng(std::random_device()()),
            dist(0, genotypeSize - 1) {}

    void mutate(std::vector<int> &genotype) override {
        int first = dist(rng);
        int last = dist(rng);
        while (genotype[first] == genotype[last]) {
            last = dist(rng);
        }
        std::swap(genotype[first], genotype[last]);
    }
};


#endif //ALG_OPT_SWAP_H
