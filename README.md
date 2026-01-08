# ACM_memoryManagement

Memory Management Simulator

A command-line simulator that models key operating system memory management concepts, including dynamic memory allocation, fragmentation analysis, and multilevel CPU cache behavior.
The project focuses on correctness, modular design, and clear observation of system-level trade-offs.

Features
Physical Memory Management

Simulates a contiguous block of physical memory

Supports dynamic allocation and deallocation

Implements block splitting and coalescing

Allocation strategies:

First Fit

Best Fit

Worst Fit

Fragmentation & Statistics

Memory utilization

External fragmentation

Allocation success/failure rate

Internal fragmentation (minimal due to exact block sizing)

Multilevel Cache Simulation

Two-level cache hierarchy (L1, L2)

Direct-mapped caches

FIFO replacement policy

Write-through write policy

Miss penalty propagation

Cache hit/miss tracking

Average Memory Access Time (AMAT)

Interactive CLI

Allocate, free, and visualize memory

Switch allocation strategies at runtime

Simulate cache reads and writes

View detailed memory and cache statistics

Project Structure
memory-simulator/
├─ src/
│  ├─ allocator/        # Allocation algorithms
│  ├─ memory/           # Memory manager
│  ├─ cache/            # Cache simulation
│  ├─ cli/              # Command-line interface
│  └─ main.cpp
├─ tests/               # Sample workloads and logs
├─ docs/                # Design document
├─ Makefile
└─ README.md

Build & Run
Build
make

Run
./memsim

CLI Commands
Memory Management
init memory <size>
set allocator <first_fit | best_fit | worst_fit>
malloc <size>
free <block_id>
dump
stats

Cache Simulation
cache_read <address>
cache_write <address>
cache_stats

Testing

Sample input workloads and logs are provided in the tests/ directory:

Memory allocation workloads

Cache access workloads

Conceptual virtual address access logs

Expected correctness criteria

Tests are executed manually via the CLI due to deterministic behavior.

Design Notes

Buddy allocation and virtual memory paging are not implemented (optional features)

Their designs are described conceptually in the design document

Cache simulation and memory allocation are intentionally decoupled

Demo

A short terminal recording demonstrates:

Memory allocation and deallocation

Fragmentation and statistics

Cache hits, misses, and access time behavior

Conclusion

This simulator provides a clear, modular, and accurate model of core OS memory management mechanisms, emphasizing algorithmic correctness and performance trade-offs.
