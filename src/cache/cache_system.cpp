#include "cache_system.h"
#include <iostream>

CacheSystem::CacheSystem()
    : l1(64, 16, 1),      // 64B cache, 16B block, 1 cycle
      l2(256, 16, 10),    // 256B cache, 16B block, 10 cycles
      memoryLatency(100),
      totalAccessTime(0),
      totalAccesses(0) {}

void CacheSystem::read(size_t address) {
    totalAccesses++;

    // L1 access
    totalAccessTime += l1.getLatency();
    if (l1.access(address)) return;

    // L2 access
    totalAccessTime += l2.getLatency();
    if (l2.access(address)) return;

    // Memory access
    totalAccessTime += memoryLatency;
}

void CacheSystem::write(size_t address) {
    totalAccesses++;

    // Write-through policy
    totalAccessTime += l1.getLatency();
    l1.access(address);

    totalAccessTime += l2.getLatency();
    l2.access(address);

    totalAccessTime += memoryLatency;
}

void CacheSystem::printStats() const {
    std::cout << "\n--- Cache Statistics ---\n";
    std::cout << "L1 Hits: " << l1.getHits() << "\n";
    std::cout << "L1 Misses: " << l1.getMisses() << "\n";
    std::cout << "L2 Hits: " << l2.getHits() << "\n";
    std::cout << "L2 Misses: " << l2.getMisses() << "\n";

    std::cout << "Total Accesses: " << totalAccesses << "\n";
    std::cout << "Total Access Time: " << totalAccessTime << " cycles\n";

    if (totalAccesses > 0) {
        std::cout << "Average Access Time: "
                  << (double)totalAccessTime / totalAccesses
                  << " cycles\n";
    }
}
