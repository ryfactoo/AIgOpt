#ifndef ALG_OPT_MUTATIONNEIGHBOURS_H
#define ALG_OPT_MUTATIONNEIGHBOURS_H


#include <memory>
#include "INeighbours.h"
#include "Mutate/IMutate.h"

class MutationNeighbours final: public INeighbours {
private:
    std::unique_ptr<IMutate> mut;
    int size;
public:
    MutationNeighbours(std::unique_ptr<IMutate> mut, int size);
    void generateNeighbours(const Solution &base, std::vector<Solution> &output) override;
};


#endif //ALG_OPT_MUTATIONNEIGHBOURS_H
