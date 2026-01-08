#ifndef CACHE_LEVEL_H
#define CACHE_LEVEL_H

#include <vector>
#include <cstddef>

struct CacheLine {
    bool valid;
    size_t tag;
};

class CacheLevel {
private:
    size_t cacheSize;
    size_t blockSize;
    size_t numLines;
    size_t latency;

    std::vector<CacheLine> lines;

    // stats
    size_t hits;
    size_t misses;

public:
    CacheLevel(size_t cacheSize, size_t blockSize, size_t latency);

    bool access(size_t address); // read or write
    size_t getLatency() const;

    size_t getHits() const;
    size_t getMisses() const;
};

#endif
