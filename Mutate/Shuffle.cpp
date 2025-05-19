#include <algorithm>
#include "Shuffle.h"

Shuffle::Shuffle(int genotypeSize) :
        IMutate(genotypeSize),
        rng(std::random_device()()),
        firstDist(0, genotypeSize - 1),
        secondDist(0, genotypeSize - 2) {}

void Shuffle::mutate(std::vector<int> &genotype) {
    int first = firstDist(rng);
    int last = secondDist(rng);
    if (first <= last)
        last += 1;
    else
        std::swap(first, last);
    std::shuffle(genotype.begin() + first, genotype.begin() + last, rng);
}
