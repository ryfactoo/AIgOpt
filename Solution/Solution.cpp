#include <algorithm>
#include <utility>
#include "Solution.h"
#include <climits>
#include <iostream>

int Solution::getScore() const {
    return score;
}

const std::vector<int> &Solution::getGenotype() const {
    return genotype;
}

std::vector<int> &Solution::getMutableGenotype() {
    evaluatedFor = nullptr;
    return genotype;
}

bool Solution::operator==(const Solution &rhs) const {
    return evaluatedFor != nullptr && evaluatedFor == rhs.evaluatedFor && score == rhs.score && genotype == rhs.genotype;
}

bool Solution::operator!=(const Solution &rhs) const {
    return !(rhs == *this);
}

void Solution::evaluate(const IEvaluator &problem) {
    score = problem.evaluate(genotype);
    evaluatedFor = &problem;
}

Solution::Solution(const std::vector<int> &genotype, int score, const IEvaluator* evaluatedFor)
        : genotype(genotype), score(score), evaluatedFor(evaluatedFor) {}

Solution::Solution(std::vector<int> &&genotype, int score, const IEvaluator* evaluatedFor)
        : genotype(std::move(genotype)), score(score), evaluatedFor(evaluatedFor) {}

Solution::Solution(const std::vector<int> &genotype)
        : genotype(genotype), score(INT_MAX), evaluatedFor(nullptr) {}

Solution::Solution(std::vector<int> &&genotype)
        : genotype(std::move(genotype)), score(INT_MAX), evaluatedFor(nullptr) {}

Solution::Solution(std::vector<int> genotype, boost::random::xoshiro256pp &rng)
        : genotype(std::move(genotype)), score(INT_MAX), evaluatedFor(nullptr) {
    std::shuffle(std::begin(this->genotype), std::end(this->genotype), rng);
}

Solution::Solution(const Solution &other) = default;

Solution::Solution(Solution &&other) noexcept
        : genotype(std::move(other.genotype)), score(other.score), evaluatedFor(other.evaluatedFor) {}

Solution &Solution::operator=(Solution &&other) noexcept {
    std::swap(genotype, other.genotype);
    score = other.score;
    evaluatedFor = other.evaluatedFor;
    return *this;
}

Solution::Solution(): genotype(), score(INT_MAX), evaluatedFor(nullptr) {}

const IEvaluator *Solution::getEvaluatedFor() {
    return evaluatedFor;
}

bool Solution::isEvaluated() {
    return evaluatedFor != nullptr;
}

Solution &Solution::operator=(const Solution &other) = default;

void Solution::printGenotype() {
    for (int n : genotype) {
        std::cout << n << ' ';
    }
}