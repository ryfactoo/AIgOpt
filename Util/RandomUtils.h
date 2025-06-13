#ifndef ALG_OPT_RANDOMUTILS_H
#define ALG_OPT_RANDOMUTILS_H

#include <iostream>

template<typename T>
void print(const T &container,
           std::ostream &os = std::cout,
           std::string_view end = "\n",
           std::string_view begin = "",
           std::string_view sep = " "
) {
    os << begin;
    auto iter = container.begin();
    if (iter != container.end()) {
        os << *iter;
        ++iter;
    }
    for (; iter != container.end(); ++iter) {
        os << sep << *iter;
    }
    os << end;
}

#endif //ALG_OPT_RANDOMUTILS_H
