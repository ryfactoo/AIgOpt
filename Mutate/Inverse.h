#ifndef ALG_OPT_INVERSE_H
#define ALG_OPT_INVERSE_H


#include <random>
#include <algorithm>
#include "IMutate.h"

class Inverse : public IMutate {
private:
    std::mt19937 rng;
    std::uniform_int_distribution<> dist;
public:
    explicit Inverse(int genotypeSize) :
            IMutate(genotypeSize),
            rng(std::random_device()()),
            dist(0, genotypeSize) {}
    void mutate(std::vector<int> &genotype) override {
        int first = dist(rng);
        int last = dist(rng);
        while (genotype[first] == genotype[last]) {
            last = dist(rng);
        }
        if (first > last)
            std::swap(first, last);
        std::reverse(genotype.begin() + first, genotype.begin() + last);
    }
};


#endif //ALG_OPT_INVERSE_H
