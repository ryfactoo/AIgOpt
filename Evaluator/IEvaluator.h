#ifndef ALG_OPT_IEVALUATOR_H
#define ALG_OPT_IEVALUATOR_H


#include <random>

/**
 * Base class for permutation problem definition.
 * Contains example encoding for solution,
 * and method for evaluating solutions
 */
class IEvaluator {
private:
    std::string instanceName;
protected:
    std::vector<int> genotypeValues;
public:
    IEvaluator(int size, std::string &instanceName) : genotypeValues(size, 0), instanceName(instanceName) {}

    [[nodiscard]] virtual int evaluate(const std::vector<int> &genotype) const = 0;

    [[nodiscard]] int getGenotypeSize() const {
        return genotypeValues.size();
    }

    [[nodiscard]] const std::vector<int> &getGenotypeValues() const {
        return genotypeValues;
    }

    [[nodiscard]] virtual std::vector<int> getFenotype(const std::vector<int>& genotype) const = 0;

    virtual ~IEvaluator() = default;
};



#endif //ALG_OPT_IEVALUATOR_H
