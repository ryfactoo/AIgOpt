#include "TabuList.h"
#include <algorithm>

bool TabuList::contains(const Solution &solution) const {
    auto xd = std::find(circularBuffer.begin(), circularBuffer.end(), solution) != circularBuffer.end();
    return xd;
}

void TabuList::push_back(const Solution &solution) {
    if (circularBuffer.size() == maxSize)
        circularBuffer.pop_front();
    circularBuffer.push_back(solution);
}

void TabuList::push_back(Solution &&solution) {
    circularBuffer.push_back(std::move(solution));
}

TabuList::TabuList(int maxSize): circularBuffer(maxSize), maxSize(maxSize) {}
//TabuList::TabuList(int maxSize): circularBuffer(), maxSize(maxSize) {}
