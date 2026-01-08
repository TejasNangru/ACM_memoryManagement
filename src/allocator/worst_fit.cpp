#include "allocator.h"

class WorstFitAllocator : public Allocator {
public:
    std::list<Block>::iterator
    findBlock(std::list<Block>& blocks, size_t size) override {
        auto worst = blocks.end();
        size_t maxSize = 0;

        for (auto it = blocks.begin(); it != blocks.end(); ++it) {
            if (it->free && it->size >= size && it->size > maxSize) {
                maxSize = it->size;
                worst = it;
            }
        }
        return worst;
    }
};
