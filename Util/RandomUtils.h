#ifndef ALG_OPT_RANDOMUTILS_H
#define ALG_OPT_RANDOMUTILS_H

#include <iostream>

template <typename T>
void print(const T& container) {
    for (const auto& elem : container) {
        std::cout << elem << ' ';
    }
    std::cout << '\n';
}

#endif //ALG_OPT_RANDOMUTILS_H
