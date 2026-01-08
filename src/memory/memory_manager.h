#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <list>
#include <memory>
#include <cstddef>

#include "../allocator/block.h"
#include "../allocator/allocator.h"

class MemoryManager {
private:
    size_t totalSize;
    std::list<Block> blocks;
    int nextId;
    std::unique_ptr<Allocator> allocator;

    size_t allocatedMemory;
    int allocSuccess;
    int allocFailure;

public:
    MemoryManager(size_t size);

    void setAllocator(Allocator* alloc);
    int allocate(size_t size);
    void freeBlock(int id);
    void dumpMemory() const;
    void printStats() const;
};

#endif
