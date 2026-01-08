#include "cache_level.h"

CacheLevel::CacheLevel(size_t cSize, size_t bSize, size_t lat)
    : cacheSize(cSize),
      blockSize(bSize),
      latency(lat),
      hits(0),
      misses(0) {

    numLines = cacheSize / blockSize;
    lines.resize(numLines);

    for (auto &line : lines) {
        line.valid = false;
        line.tag = 0;
    }
}

bool CacheLevel::access(size_t address) {
    size_t blockAddr = address / blockSize;
    size_t index = blockAddr % numLines;
    size_t tag = blockAddr / numLines;

    CacheLine &line = lines[index];

    if (line.valid && line.tag == tag) {
        hits++;
        return true;  // HIT
    } else {
        misses++;
        line.valid = true;
        line.tag = tag;  // FIFO replace
        return false; // MISS
    }
}

size_t CacheLevel::getLatency() const {
    return latency;
}

size_t CacheLevel::getHits() const {
    return hits;
}

size_t CacheLevel::getMisses() const {
    return misses;
}
