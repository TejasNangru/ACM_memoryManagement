#include "memory_manager.h"
#include <iostream>

// Constructor
MemoryManager::MemoryManager(size_t size)
    : totalSize(size),
      nextId(1),
      allocator(nullptr),
      allocatedMemory(0),
      allocSuccess(0),
      allocFailure(0) {
    blocks.emplace_back(0, size);
}


// ✅ REQUIRED: allocator setter
void MemoryManager::setAllocator(Allocator* alloc) {
    allocator.reset(alloc);
}

int MemoryManager::allocate(size_t size) {
    if (!allocator) {
        std::cout << "Allocator not set\n";
        return -1;
    }

    auto it = allocator->findBlock(blocks, size);
    if (it == blocks.end()) {
        std::cout << "Allocation failed\n";
        allocFailure++;
        return -1;
    }

    int id = nextId++;
    allocSuccess++;
    allocatedMemory += size;

    if (it->size > size) {
        Block newBlock(it->start + size, it->size - size);
        blocks.insert(std::next(it), newBlock);
    }

    it->size = size;
    it->free = false;
    it->id = id;

    std::cout << "Allocated block id=" << id
              << " at address=" << it->start << "\n";
    return id;
}


// Free + coalesce
void MemoryManager::freeBlock(int id) {
    for (auto it = blocks.begin(); it != blocks.end(); ++it) {
        if (!it->free && it->id == id) {
            allocatedMemory -= it->size;
            it->free = true;
            it->id = -1;

            // Merge with next
            auto next = std::next(it);
            if (next != blocks.end() && next->free) {
                it->size += next->size;
                blocks.erase(next);
            }

            // Merge with previous
            if (it != blocks.begin()) {
                auto prev = std::prev(it);
                if (prev->free) {
                    prev->size += it->size;
                    blocks.erase(it);
                }
            }

            std::cout << "Block " << id << " freed and merged\n";
            return;
        }
    }
    std::cout << "Invalid block id\n";
}

// Memory dump
void MemoryManager::dumpMemory() const {
    for (const auto& block : blocks) {
        std::cout << "[" << block.start
                  << " - " << block.start + block.size - 1
                  << "] ";
        if (block.free)
            std::cout << "FREE\n";
        else
            std::cout << "USED (id=" << block.id << ")\n";
    }
}

void MemoryManager::printStats() const {
    size_t freeMemory = totalSize - allocatedMemory;
    size_t largestFreeBlock = 0;
    int freeBlocks = 0;

    for (const auto& block : blocks) {
        if (block.free) {
            freeBlocks++;
            if (block.size > largestFreeBlock)
                largestFreeBlock = block.size;
        }
    }

    double externalFragmentation = 0.0;
    if (freeMemory > 0) {
        externalFragmentation =
            100.0 * (1.0 - (double)largestFreeBlock / freeMemory);
    }

    double utilization =
        100.0 * (double)allocatedMemory / totalSize;

    std::cout << "\n--- Memory Statistics ---\n";
    std::cout << "Total memory: " << totalSize << "\n";
    std::cout << "Used memory: " << allocatedMemory << "\n";
    std::cout << "Free memory: " << freeMemory << "\n";
    std::cout << "Free blocks: " << freeBlocks << "\n";
    std::cout << "Memory utilization: " << utilization << "%\n";
    std::cout << "External fragmentation: "
              << externalFragmentation << "%\n";
    std::cout << "Alloc success: " << allocSuccess << "\n";
    std::cout << "Alloc failure: " << allocFailure << "\n";
}
