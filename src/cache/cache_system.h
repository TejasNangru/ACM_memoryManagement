#ifndef CACHE_SYSTEM_H
#define CACHE_SYSTEM_H

#include "cache_level.h"

class CacheSystem {
private:
    CacheLevel l1;
    CacheLevel l2;

    size_t memoryLatency;
    size_t totalAccessTime;
    size_t totalAccesses;

public:
    CacheSystem();

    void read(size_t address);
    void write(size_t address);

    void printStats() const;
};

#endif
