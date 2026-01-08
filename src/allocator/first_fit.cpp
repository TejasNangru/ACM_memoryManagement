#include "allocator.h"

class FirstFitAllocator : public Allocator {
public:
    std::list<Block>::iterator
    findBlock(std::list<Block>& blocks, size_t size) override {
        for (auto it = blocks.begin(); it != blocks.end(); ++it) {
            if (it->free && it->size >= size)
                return it;
        }
        return blocks.end();
    }
};
