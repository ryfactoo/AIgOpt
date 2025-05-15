#ifndef ALG_OPT_INEIGHBOURS_H
#define ALG_OPT_INEIGHBOURS_H

#include "Solution/Solution.h"

class INeighbours {
public:
    virtual ~INeighbours() = default;
    virtual void generateNeighbours(const Solution &base, std::vector<Solution> &output) = 0;
};


#endif //ALG_OPT_INEIGHBOURS_H
