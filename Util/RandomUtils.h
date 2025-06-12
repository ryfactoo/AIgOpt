#ifndef ALG_OPT_RANDOMUTILS_H
#define ALG_OPT_RANDOMUTILS_H

#include <iostream>

template <typename T>
void print(const T& container, std::string_view end = "\n", std::ostream& os = std::cout) {
    for (const auto& elem : container) {
        os << elem << ' ';
    }
    os << end;
}

#endif //ALG_OPT_RANDOMUTILS_H
