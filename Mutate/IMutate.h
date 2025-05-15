#ifndef ALG_OPT_IMUTATE_H
#define ALG_OPT_IMUTATE_H


class IMutate {
protected:
    int genotypeSize;
public:
    explicit IMutate(int genotypeSize): genotypeSize(genotypeSize) {};
    [[nodiscard]] int getGenotypeSize() const { return genotypeSize; }
    virtual void mutate(std::vector<int> &genotype) = 0;
    virtual ~IMutate() = default;
};

#endif //ALG_OPT_IMUTATE_H
