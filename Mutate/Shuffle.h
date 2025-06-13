#ifndef ALG_OPT_SHUFFLE_H
#define ALG_OPT_SHUFFLE_H


#include <random>
#include "IMutate.h"

class Shuffle : public IMutate {
private:
    boost::random::xoshiro256pp rng;
    std::uniform_int_distribution<> dist;
public:
    explicit Shuffle(int genotypeSize) :
            IMutate(genotypeSize),
            rng(std::random_device()()),
            dist(0, genotypeSize - 1) {}

    void mutate(std::vector<int> &genotype) override {
        int first = dist(rng);
        int last = dist(rng);
        while (genotype[first] == genotype[last]) {
            last = dist(rng);
        }
        if (first > last)
            std::swap(first, last);
        std::shuffle(genotype.begin() + first, genotype.begin() + last, rng);
    }
};


#endif //ALG_OPT_SHUFFLE_H
