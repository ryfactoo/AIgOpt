#include "MutationNeighbours.h"

MutationNeighbours::MutationNeighbours(std::unique_ptr<IMutate> mut, int size) : mut(std::move(mut)), size(size) {}

void MutationNeighbours::generateNeighbours(const Solution &base, std::vector<Solution> &output) {
    output.reserve(output.size() + size);
    output.insert(output.end(), size, base);
    for (auto it = output.rbegin(); it != output.rbegin() + size; ++it) {
        mut->mutate(it->getMutableGenotype());
    }
}
