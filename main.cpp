#include <iostream>
#include <BS_thread_pool.hpp>
#include "CLI/CLI.hpp"
#include "Util/ProblemLoader.h"
#include "Util/MetaheuristicLoader.h"
#include "Evaluator/CVRP2.h"
#include "Util/RandomUtils.h"
#include "Heuristic/CVRPGreedy.h"


int main(int argc, char *argv[]) {
    enum class Evaluators {
        CVRP,
        CVRP2
    };
    std::map<std::string, Evaluators> evaluatorMapping{
            {"cvrp",  Evaluators::CVRP},
            {"cvrp2", Evaluators::CVRP2},
    };

    CLI::App app{"AO course project"};
    argv = app.ensure_utf8(argv);
    Evaluators evaluator;
    app.add_option("-e, --evaluator", evaluator, "Evaluator for problem")
            ->required()
            ->transform(CLI::CheckedTransformer(evaluatorMapping));

    std::filesystem::path instancePath;
    app.add_option("-i, --instance", instancePath, "Path to problem instance")
            ->required()
            ->check(CLI::ExistingFile);

    std::filesystem::path cfgPath;
    app.add_option("-c, --config", cfgPath, "Config for solver")
            ->required()
            ->check(CLI::ExistingFile);

    std::filesystem::path outputPath;
    auto logOption = app.add_option("-l, --logs", outputPath, "Output path (directory)");

    unsigned int threads = 1;
    app.add_option("-t, --threads", threads, "Allows running multiple solvers in parallel, by default all available cores")
            ->default_val(std::thread::hardware_concurrency())
            ->check(CLI::PositiveNumber);

    unsigned int runNum = 1;
    app.add_option("-n, --repeats", runNum, "Runs solver multiple times")
            ->default_val(1)
            ->check(CLI::PositiveNumber);


    CLI11_PARSE(app, argc, argv);


    threads = std::min(runNum, threads);
    std::unique_ptr<IEvaluator> problem;
    if (evaluator == Evaluators::CVRP) {
        problem = loadCVRP<CVRP>(instancePath);
    } else if (evaluator == Evaluators::CVRP2) {
        problem = loadCVRP<CVRP2>(instancePath);
        auto xd = cvrp_greedy(*dynamic_cast<CVRP2*>(problem.get()));
        std::cerr << "Greedy solution:\n" << xd.getScore() << ",\"";
        print(xd.getGenotype(), "\"\n", std::cerr);
    } else {
        std::cerr << "Unknown evaluator type\n";
        return 1;
    }
    auto jsonConfig = readJson(cfgPath);
    bool logging = (bool) (*logOption);
    if (logging) {
        outputPath = std::filesystem::absolute(outputPath);
        std::cerr << "Writing solver logs to: " << outputPath.string() << '\n';
        std::filesystem::create_directories(outputPath);
    }

    std::vector<Solution> results(runNum);

    BS::thread_pool pool(threads);
    auto start = std::chrono::system_clock::now();
    for (int i = 0; i < runNum; ++i) {
        pool.detach_task([&, i]() {
            auto solver = parseMetaheuristicJson(jsonConfig, *problem, logging);
            solver->run();
            results[i] = solver->getBestSolution();
            if (logging) {
                std::ofstream logFile(outputPath / (std::to_string(i+1) + ".csv"));
                PopulationStats::writeHeaders(logFile);
                solver->dumpLogs(logFile);
                logFile.close();
            }
        });
    }
    pool.wait();
    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "score,fenotype\n";
    for (auto& sol: results) {
        std::cout << sol.getScore() << ",\"";
        print(problem->getFenotype(sol.getGenotype()), "\"\n");
    }
    std::cerr << "Took " << elapsed.count() << " ms\n";
    return 0;
}
