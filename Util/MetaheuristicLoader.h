#ifndef ALG_OPT_METAHEURISTICLOADER_H
#define ALG_OPT_METAHEURISTICLOADER_H

#include <fstream>
#include "boost/json.hpp"
#include "Evaluator/IEvaluator.h"
#include "Metaheuristic/IMetaheuristic.h"
#include "Mutate/Swap.h"
#include "Mutate/Inverse.h"
#include "NeighbourhoodGen/INeighbours.h"
#include "NeighbourhoodGen/MutationNeighbours.h"
#include "Metaheuristic/TabuSearch.h"
#include "Mutate/Shuffle.h"

namespace bj = boost::json;

bj::value readJson(const std::filesystem::path& path) {
    std::ifstream file(path);
    if (!file) {
        throw std::runtime_error("Unable to open file: " + path.string());
    }

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    boost::system::error_code ec;
    auto jsonValue = bj::parse(content, ec);

    if (ec) {
        throw std::runtime_error("JSON parsing error: " + ec.message());
    }

    return jsonValue;
}

std::unique_ptr<IMutate> parseMutateJson(bj::value& jv, const IEvaluator& problem) {
    auto type = bj::value_to<std::string>(jv.at("type"));
    if (type == "swap") {
        return std::make_unique<Swap>(problem.getGenotypeSize());
    } else if (type == "inverse") {
        return std::make_unique<Inverse>(problem.getGenotypeSize());
    } else if (type == "shuffle") {
        return std::make_unique<Shuffle>(problem.getGenotypeSize());
    } else {
        throw std::runtime_error("Unknown mutation type: " + type);
    }
}

std::unique_ptr<INeighbours> parseNeighboursJson(bj::value& jv, const IEvaluator& problem) {
    auto type = bj::value_to<std::string>(jv.at("type"));
    if (type == "mutation") {
        auto mut = parseMutateJson(jv.at("mut"), problem);
        auto size = bj::value_to<int>(jv.at("size"));
        return std::make_unique<MutationNeighbours>(std::move(mut), size);
    } else {
        throw std::runtime_error("Unknown neighbours type: " + type);
    }
}

std::unique_ptr<IMetaheuristic> parseMetaheuristicJson(bj::value& jv, const IEvaluator& problem, bool logging){
    auto type = bj::value_to<std::string>(jv.at("type"));
    std::random_device rd;
    boost::random::xoshiro256pp rng(rd());
    if (type == "tabu") {
        auto iter = bj::value_to<int>(jv.at("iterations"));
        auto tabuSize = bj::value_to<int>(jv.at("tabu_size"));
        auto neighbours = parseNeighboursJson(jv.at("neighbours"), problem);
        Solution initSolution(problem.getGenotypeValues(), rng);
        return std::make_unique<TabuSearch>(problem, iter, tabuSize, std::move(neighbours), initSolution, logging);
    } else {
        throw std::runtime_error("Unknown metaheuristic type: " + type);
    }
}

#endif //ALG_OPT_METAHEURISTICLOADER_H
