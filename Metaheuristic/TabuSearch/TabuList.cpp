#include "TabuList.h"
#include <algorithm>

bool TabuList::contains(const Solution &solution) const {
//    auto xd = std::find(circularBuffer.begin(), circularBuffer.end(), solution) != circularBuffer.end();
    auto xd = hashTable.find(&solution) != hashTable.end();
    return xd;
}

void TabuList::push_back(const Solution &solution) {
    if (circularBuffer.size() == maxSize) {
        hashTable.erase(&(circularBuffer.front()));
        circularBuffer.pop_front();
    }
    circularBuffer.push_back(solution);
    hashTable.insert(&circularBuffer.back());
}

void TabuList::push_back(Solution &&solution) {
    if (circularBuffer.size() == maxSize) {
        hashTable.erase(&(circularBuffer.front()));
        circularBuffer.pop_front();
    }
    circularBuffer.push_back(solution);
    hashTable.insert(&circularBuffer.back());
}

TabuList::TabuList(int maxSize): circularBuffer(), maxSize(maxSize) {}
