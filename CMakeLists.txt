cmake_minimum_required(VERSION 3.30)
project(alg_opt)

set(CMAKE_CXX_STANDARD 17)
set(VCPKG_MANIFEST_MODE ON)

find_package(boost_multi_array CONFIG REQUIRED)
find_package(boost_json CONFIG REQUIRED)
find_package(unofficial-vincentlaucsb-csv-parser CONFIG REQUIRED)
find_package(CLI11 CONFIG REQUIRED)
find_path(BSHOSHANY_THREAD_POOL_INCLUDE_DIRS "BS_thread_pool.hpp")

add_executable(alg_opt main.cpp
        Metaheuristic/IMetaheuristic.h
        Evaluator/IEvaluator.h
        Solution/Solution.h
        Mutate/IMutate.h
        Metaheuristic/TabuSearch.h
        Metaheuristic/TabuSearch/TabuList.h
        Evaluator/CVRP.h
        NeighbourhoodGen/INeighbours.h
        NeighbourhoodGen/MutationNeighbours.h
        Util/PopulationStats.h
        Solution/Solution.cpp
        Solution/Solution.cpp
        NeighbourhoodGen/MutationNeighbours.cpp
        Evaluator/CVRP.cpp
        Util/MetaheuristicLoader.h
        Mutate/Inverse.cpp
        Mutate/Shuffle.cpp
        Mutate/Swap.cpp
        Metaheuristic/TabuSearch/TabuList.cpp
        Metaheuristic/TabuSearch/TabuSearch.cpp
)

target_include_directories(alg_opt
        PRIVATE ${CMAKE_SOURCE_DIR}
        PRIVATE ${BSHOSHANY_THREAD_POOL_INCLUDE_DIRS}
)

target_link_libraries(alg_opt
        PRIVATE Boost::multi_array
        PRIVATE Boost::json
        PRIVATE unofficial::vincentlaucsb-csv-parser::csv
        PRIVATE CLI11::CLI11
)
