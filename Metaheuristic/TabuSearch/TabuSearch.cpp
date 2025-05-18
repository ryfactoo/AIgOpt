#include "Metaheuristic/TabuSearch.h"

TabuSearch::TabuSearch(
        const IEvaluator &problem,
        int iterations,
        int tabuSize,
        std::unique_ptr<INeighbours> neighbourGen,
        Solution &initialSolution,
        bool enableLogging) :
        IMetaheuristic(problem),
        _iterations(iterations),
        tabu(tabuSize),
        neighbourGen(std::move(neighbourGen)),
        current(initialSolution),
        enableLogging(enableLogging)
        {
    current.evaluate(problem);
    best = current;
    if (enableLogging)
        logger.reserve(iterations);
}

void TabuSearch::run() {
    for (int i = 0; i < _iterations; ++i) {
        neighbourGen->generateNeighbours(current, neighbourhood);
        auto bestNeighbour = findBestNeighbour();
        if (bestNeighbour) {
            current = *bestNeighbour;
            tabu.push_back(*bestNeighbour);
            if (current.getScore() < best.getScore())
                best = current;
        }
        if (enableLogging) {
            logger.ratePopulation(neighbourhood, current.getScore());
        }
        neighbourhood.clear();
    }
}

Solution* TabuSearch::findBestNeighbour() {
    Solution* bestNeighbour = nullptr;
    for (auto& n: neighbourhood) {
        n.evaluate(problem);
        if (!tabu.contains(n) && (bestNeighbour == nullptr || n.getScore() < bestNeighbour->getScore())){
            bestNeighbour = &n;
        }

    }
    return bestNeighbour;
}

int TabuSearch::getIterations() const {
    return _iterations;
}

void TabuSearch::setIterations(int iterations) {
    TabuSearch::_iterations = iterations;
}

const Solution &TabuSearch::getBestSolution() const {
    return best;
}

void TabuSearch::dumpLogs(std::ostream &os) {
    logger.dump(os);
}

