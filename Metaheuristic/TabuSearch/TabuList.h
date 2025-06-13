#ifndef ALG_OPT_TABULIST_H
#define ALG_OPT_TABULIST_H

#include <unordered_set>
#include <list>
#include "Solution/Solution.h"


struct SolutionPointerHash {
    std::size_t operator()(const Solution* solution) const {
        return std::hash<int>()(solution->getScore());
    }
};

struct SolutionPointerEqual {
    bool operator()(const Solution* lhs, const Solution* rhs) const {
        return *lhs == *rhs;
    }
};


class TabuList {
private:
    std::list<Solution> circularBuffer;
    std::unordered_set<const Solution*, SolutionPointerHash, SolutionPointerEqual> hashTable;
    int maxSize;
public:
    explicit TabuList(int size);
    [[nodiscard]] bool contains(const Solution &solution) const;
    void push_back(const Solution &solution);
    void push_back(Solution &&solution);
};


#endif //ALG_OPT_TABULIST_H
