#ifndef ALG_OPT_SOLUTION_H
#define ALG_OPT_SOLUTION_H

#include <vector>
#include <random>
#include <boost/random/xoshiro.hpp>
#include "Evaluator/IEvaluator.h"

class Solution {
private:
    std::vector<int> genotype;
    int score;
    const IEvaluator* evaluatedFor;
public:
    Solution();
    explicit Solution(const std::vector<int> &genotype);
    explicit Solution(std::vector<int> &&genotype);
    Solution(const std::vector<int> &genotype, int score, const IEvaluator* evaluatedFor);
    Solution(std::vector<int> &&genotype, int score, const IEvaluator* evaluatedFor);
    Solution(const Solution& other);
    Solution(Solution&& other) noexcept;
    Solution(std::vector<int> genotype, boost::random::xoshiro256pp& rng);
    Solution& operator=(const Solution &other);
    Solution& operator=(Solution &&other) noexcept;

    [[nodiscard]] int getScore() const;
    [[nodiscard]] const std::vector<int> &getGenotype() const;
    [[nodiscard]] std::vector<int> &getMutableGenotype();
    bool isEvaluated();
    const IEvaluator* getEvaluatedFor();
    void evaluate(const IEvaluator &problem);
    ~Solution() = default;
    bool operator==(const Solution &rhs) const;
    bool operator!=(const Solution &rhs) const;

    void printGenotype();
};


#endif //ALG_OPT_SOLUTION_H
