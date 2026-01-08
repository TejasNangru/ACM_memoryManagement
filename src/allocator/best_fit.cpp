#include "allocator.h"
#include <limits>

class BestFitAllocator : public Allocator {
public:
    std::list<Block>::iterator
    findBlock(std::list<Block>& blocks, size_t size) override {
        auto best = blocks.end();
        size_t minDiff = std::numeric_limits<size_t>::max();

        for (auto it = blocks.begin(); it != blocks.end(); ++it) {
            if (it->free && it->size >= size) {
                size_t diff = it->size - size;
                if (diff < minDiff) {
                    minDiff = diff;
                    best = it;
                }
            }
        }
        return best;
    }
};

