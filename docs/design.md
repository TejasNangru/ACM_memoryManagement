# Memory Management Simulator — Design & Implementation

A modular, interactive Memory Management Simulator that models how an operating system manages dynamic memory and a two-level cache hierarchy. This repository contains an educational user-space simulator focused on allocation strategies, fragmentation analysis, and cache behavior rather than an OS kernel.

---

## Table of Contents

- 1. Overview
- 2. System Architecture
- 3. Physical Memory Simulation
  - 3.1 Memory Model
  - 3.2 Block Representation
- 4. Dynamic Memory Allocation Strategies
  - 4.1 First Fit
  - 4.2 Best Fit
  - 4.3 Worst Fit
  - 4.4 Allocation and Deallocation
- 5. Fragmentation and Memory Statistics
  - 5.1 Memory Metrics
  - 5.2 External Fragmentation
  - 5.3 Internal Fragmentation
- 6. Multilevel Cache Simulation
  - 6.1 Cache Architecture
  - 6.2 Cache Replacement Policy
- 7. Cache Access and Write Policy
  - 7.1 Read Access
  - 7.2 Write Policy
- 8. Cache Performance Metrics
- 9. Command Line Interface (CLI)
  - 9.1 Memory Commands
  - 9.2 Cache Commands
- 10. Virtual Memory Simulation
- 11. Modularity and Design Principles
- 12. Limitations and Future Work
- 13. Conclusion
- Appendix: Example CLI Session

---

## 1. Overview

This project implements a Memory Management Simulator that models how an operating system manages memory at a conceptual level. The simulator focuses on dynamic memory allocation, fragmentation analysis, and cache behavior, using user-space code and well-defined data structures.

The goal is to simulate OS memory-management mechanisms—allocation strategies, block coalescing, cache hierarchies, and performance trade-offs—while providing an interactive CLI to observe memory and cache behavior in real time.

---

## 2. System Architecture

The simulator is divided into independent subsystems:

- Physical Memory Manager  
- Allocation Strategy Modules (policy layer)  
- Cache Simulation Subsystem  
- Command Line Interface (CLI)  
- Statistics and Reporting

These subsystems are modular and loosely coupled so that allocation policies, cache policies, and the core mechanism (bookkeeping and access simulation) remain independent.

Architecture (high level):

```
+-----------------+     +-----------------------+
|     CLI         |<--->|  Statistics & Reporter|
+-----------------+     +-----------------------+
       |                           ^
       v                           |
+-----------------+    +---------------------+
| Physical Memory |<-->| Allocation Strategies|
|    Manager      |    +---------------------+
+-----------------+
       ^
       |
+-----------------+
| Cache Simulator |
+-----------------+
```

---

## Buddy Allocation System (Conceptual Design)

The buddy allocation system is a well-known dynamic memory allocation technique that manages memory in blocks whose sizes are powers of two. In this approach, the total memory size is assumed to be a power of two and is initially available as a single large free block.

When a memory request is made, the requested size is rounded up to the nearest power of two. If a free block of that size is not available, a larger block is recursively split into two equal-sized “buddy” blocks until a block of the required size is obtained. One block is allocated while the remaining buddy is returned to the appropriate free list.

Each block’s buddy can be identified using an XOR operation on the block’s starting address and its size. During deallocation, if both a block and its buddy are free, they are recursively merged to form a larger block. This merging process helps reduce external fragmentation

## Virtual Memory Model and Address Translation (Conceptual)

In a virtual memory system, each process operates in its own virtual address space that is independent of physical memory. The CPU generates virtual addresses, which are translated into physical addresses using a page table maintained by the operating system.

The virtual address is divided into a page number and an offset. The page number is used to index into the page table to locate the corresponding physical frame. Each page table entry contains a valid bit, a frame number, and replacement-related metadata. If the page is not present in physical memory, a page fault occurs, triggering a page replacement algorithm to select a victim page.

Once a valid physical address is obtained, it is passed to the cache hierarchy. The cache is accessed first, and on a cache miss, the data is fetched from main memory. Cache access therefore always occurs after virtual-to-physical address translation.

In this project, virtual memory simulation was not implemented, as it was specified as an optional extension. Memory accesses in the cache simulation are representational and assume a valid physical address has already been obtained. The design, however, clearly separates address translation from caching and memory access, allowing virtual memory to be integrated in the future without modifying the cache or allocation subsystems.

Address Translation Flow (Conceptual)

The conceptual flow of a memory access in a system with virtual memory can be summarized as:

CPU Virtual Address
        ↓
Page Table Lookup
        ↓
Physical Address
        ↓
L1 Cache → L2 Cache
        ↓
Main Memory


This project models the cache and memory access stages of this flow, while the virtual address translation stage is described conceptually as part of the system design

## 3. Physical Memory Simulation

### 3.1 Memory Model
- Physical memory is simulated as a single contiguous block (configurable size).
- Memory is measured and managed in bytes.
- On initialization, the entire memory is a single free block.

### 3.2 Block Representation
Each memory block contains an explicit header with:
- Starting address
- Block size (bytes)
- Allocation status (free / used)
- Allocation ID (unique identifier for allocations)

Blocks are arranged in a doubly-linked list to allow efficient:
- Insertion and deletion
- Splitting on allocation
- Coalescing on deallocation

---

## 4. Dynamic Memory Allocation Strategies

The simulator implements three classic allocation algorithms and a modular allocator interface to choose strategies at runtime.

### 4.1 First Fit
Selects the first free block large enough to satisfy an allocation request. Fast but may increase external fragmentation at the beginning of memory.

### 4.2 Best Fit
Selects the smallest free block that fits the request. Minimizes internal waste but can create many small fragments.

### 4.3 Worst Fit
Selects the largest free block. Often leaves large remainders but can lead to poor overall utilization.

### 4.4 Allocation and Deallocation
- Allocation will split a free block when the chosen block is larger than requested.
- Deallocation is performed by block ID.
- After freeing, adjacent free blocks (previous and next) are coalesced to reduce external fragmentation.
- The allocator is selected at runtime through an abstract allocator interface, enabling easy extension.

---

## 5. Fragmentation and Memory Statistics

### 5.1 Memory Metrics
The simulator tracks:
- Total memory
- Used memory
- Free memory
- Memory utilization (%)

### 5.2 External Fragmentation
External fragmentation is calculated as:

$$
\text{External Fragmentation (\%)} = 1 - \frac{\text{Largest Free Block}}{\text{Total Free Memory}}
$$

This metric indicates how scattered free memory is across address space.

### 5.3 Internal Fragmentation
Internal fragmentation is minimal because blocks are split to exact requested sizes. Consequently, internal fragmentation is normally zero and only reported (not accumulated) by the simulator.

---

## 6. Multilevel Cache Simulation

### 6.1 Cache Architecture
- Two-level cache hierarchy: L1 and L2.
- Each level is configurable:
  - Cache size (bytes)
  - Fixed block (line) size (bytes)
  - Direct-mapped organization
  - FIFO replacement policy
  - Access latency (cycles or time units)

### 6.2 Cache Replacement Policy
- FIFO (First-In-First-Out) replacement is used.
- In a direct-mapped cache a new block simply replaces whatever occupies the mapped index.
- Optional policies like LRU or LFU are not implemented (but the modular design allows future additions).

---

## 7. Cache Access and Write Policy

### 7.1 Read Access
- Read flow:
  1. Access L1.
  2. If L1 miss → access L2.
  3. If L2 miss → access main memory.
- Miss penalties and lower-level access latencies are added to the total access time.

### 7.2 Write Policy
- Write-through policy:
  - On write, data is written to memory always.
  - If the block is present in the cache, the cache line is updated (no dirty bits required).
- This simplifies consistency and avoids dirty-bit management.

---

## 8. Cache Performance Metrics
The cache subsystem tracks:
- Hits and misses per cache level (L1 and L2)
- Total number of cache accesses
- Total memory access time (accumulated)
- Average Memory Access Time (AMAT), computed by accounting for hit rates, miss penalties, and access counts

Miss penalty propagation across levels is fully accounted for in computed access times.

---

## 9. Command Line Interface (CLI)

The simulator includes an interactive CLI to perform both memory allocation and cache operations.

### 9.1 Memory Commands

```
# Initialize memory (size in bytes)
init memory <size>

# Choose allocator
set allocator <first_fit | best_fit | worst_fit>

# Allocate a block
malloc <size>

# Free a block by allocation ID
free <block_id>

# Dump memory layout (addresses, sizes, status)
dump

# Print memory statistics (utilization, fragmentation, ...)
stats
```

### 9.2 Cache Commands

```
# Simulate a read at a memory address
cache_read <address>

# Simulate a write at a memory address
cache_write <address>

# Print cache statistics for L1 and L2
cache_stats
```

The CLI supports real-time experimentation with different allocation strategies and cache configurations.

---

## 10. Virtual Memory Simulation

Virtual memory (paging) was intentionally not implemented as it was optional. Cache memory accesses are representational and do not allocate or map physical frames via the memory allocator.

---

## 11. Modularity and Design Principles

- Allocation policies are separated from the memory manager core (policy vs mechanism).
- Cache simulation is independent of the memory allocator.
- CLI is decoupled from internal subsystems and calls into well-defined interfaces.
- Centralized statistics/reporting ensures consistent metrics and fewer cross-module side effects.

This structure improves readability, testability, and extensibility.

---

## 12. Limitations and Future Work

Not implemented in this version (possible future additions):
- Buddy allocation system
- Virtual memory paging and page replacement policies (FIFO, LRU, Clock, etc.)
- Cache replacement policies other than FIFO (e.g., LRU, LFU)
- Cache hierarchy beyond two levels (L1/L2)
- More realistic associativity (set-associative caches)
- Visualization tools for memory layout and cache hits/misses

All of these can be added without reworking the architecture thanks to the modular design.

---

## 13. Conclusion

This simulator provides an educational platform to demonstrate:
- Dynamic memory allocation strategies
- Fragmentation effects and metrics
- Two-level cache behavior and its impact on access latency

The interactive CLI and modular components make it easy to experiment with policies and observe resulting system behavior.

---

## Appendix — Example CLI Session

Below is a short example showing typical usage:

```
# initialize 1 MB memory
init memory 1048576

# set allocator to best fit
set allocator best_fit

# allocate 256 bytes (returns ID 1)
malloc 256

# allocate 4096 bytes (returns ID 2)
malloc 4096

# view memory layout
dump

# free the first allocation
free 1

# view stats and fragmentation
stats

# interact with cache at address 0x2000
cache_read 8192
cache_write 8192
cache_stats
```

---


Contact / Author: TejasNangru
