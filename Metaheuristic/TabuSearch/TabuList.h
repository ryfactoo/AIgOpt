#ifndef ALG_OPT_TABULIST_H
#define ALG_OPT_TABULIST_H

#include <unordered_set>
#include <list>
#include "Solution/Solution.h"

class TabuList {
private:
    std::list<Solution> circularBuffer;
    int maxSize;
public:
    explicit TabuList(int size);
    [[nodiscard]] bool contains(const Solution &solution) const;
    void push_back(const Solution &solution);
    void push_back(Solution &&solution);
};


#endif //ALG_OPT_TABULIST_H
