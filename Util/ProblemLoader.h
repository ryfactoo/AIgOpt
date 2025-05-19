#ifndef ALG_OPT_PROBLEMLOADER_H
#define ALG_OPT_PROBLEMLOADER_H

#include <fstream>
#include <sstream>
#include <filesystem>
#include "Evaluator/IEvaluator.h"
#include "Evaluator/CVRP.h"


std::unique_ptr<CVRP> loadCVRP(const std::filesystem::path &path);

std::ifstream readProblem(const std::filesystem::path &filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Unable to open file: " + filename.string());
    }
    return file;
}

std::unique_ptr<CVRP> loadCVRP(const std::filesystem::path &path){
    auto file = readProblem(path);
    std::string name, line;
    int size, capacity;
    std::vector<std::pair<int, int>> coords;
    std::vector<int> demands;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string entry;
        iss >> entry;
        if (entry == "NAME") {
            iss.ignore(3);
            iss >> name;
        } else if (entry == "EDGE_WEIGHT_TYPE") {
            iss.ignore(3);
            std::string weights;
            iss >> weights;
            if (weights != "EUC_2D") throw std::runtime_error("Only supported type is EUC_2D, got: " + weights);
        } else if (entry == "DIMENSION") {
            iss.ignore(3);
            iss >> size;
            coords.reserve(size);
            demands.reserve(size);
        } else if (entry == "CAPACITY") {
            iss.ignore(3);
            iss >> capacity;
        } else if (entry == "NODE_COORD_SECTION") {
            for (int i = 0; i < size; i++) {
                std::getline(file, line);
                std::istringstream coordIss(line);
                coords.emplace_back();
                coordIss >> coords[i].first >> coords[i].first >> coords[i].second;
            }
        } else if (entry == "DEMAND_SECTION") {
            for (int i = 0; i < size; i++) {
                std::getline(file, line);
                std::istringstream demandIss(line);
                demandIss.ignore();
                demands.emplace_back();
                demandIss >> demands[i] >> demands[i];
            }
        }
    }
    return std::make_unique<CVRP>(name, coords, demands, capacity);
}

#endif //ALG_OPT_PROBLEMLOADER_H

