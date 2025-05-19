#include "Swap.h"

Swap::Swap(int genotypeSize) :
        IMutate(genotypeSize),
        rng(std::random_device()()),
        firstDist(0, genotypeSize - 1),
        secondDist(0, genotypeSize - 2) {}

void Swap::mutate(std::vector<int> &genotype) {
    int first = firstDist(rng);
    int last = secondDist(rng);
    last += (bool) (first <= last);
    std::swap(genotype[first], genotype[last]);
}

