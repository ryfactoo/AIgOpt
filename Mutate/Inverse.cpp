#include "Inverse.h"
#include <algorithm>

Inverse::Inverse(int genotypeSize) :
        IMutate(genotypeSize),
        rng(std::random_device()()),
        firstDist(0, genotypeSize),
        secondDist(0, genotypeSize - 1) {}

void Inverse::mutate(std::vector<int> &genotype) {
    int first = firstDist(rng);
    int last = secondDist(rng);
    if (first <= last)
        last += 1;
    else
        std::swap(first, last);
    std::reverse(genotype.begin() + first, genotype.begin() + last);
}
