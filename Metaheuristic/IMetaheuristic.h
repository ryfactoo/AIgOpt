#ifndef ALG_OPT_IMETAHEURISTIC_H
#define ALG_OPT_IMETAHEURISTIC_H


#include "Solution/Solution.h"


/**
 * Base class for solver definition.
 */
class IMetaheuristic {
protected:
    const IEvaluator &problem;
public:
    explicit IMetaheuristic(const IEvaluator& problem): problem(problem) {}
    virtual ~IMetaheuristic() = default;
    virtual void run() = 0;
    virtual void dumpLogs(std::ostream &os) = 0;
    [[nodiscard]] virtual const Solution &getBestSolution() const = 0;
};


#endif //ALG_OPT_IMETAHEURISTIC_H
