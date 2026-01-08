# ACM_memoryManagement

# DEMO-VIDEO: https://www.loom.com/share/e8ce8a1edbdb4b2aba69fc0b8113ae42?t=14

Memory Management Simulator — a command-line simulator that models key operating system memory management concepts, including dynamic memory allocation, fragmentation analysis, and a two-level CPU cache simulator.

- Focus: correctness, modular design, and clear observation of system-level trade-offs.

## Table of contents
- [Features](#features)
- [Project structure](#project-structure)
- [Quick start](#quick-start)
- [CLI commands & examples](#cli-commands--examples)
  - [Memory management commands](#memory-management-commands)
  - [Cache simulation commands](#cache-simulation-commands)
  - [Utility commands](#utility-commands)
- [Testing](#testing)
- [Design notes](#design-notes)
- [Contributing](#contributing)
- [License & contact](#license--contact)

## Features
Physical memory and allocator:
- Simulates a contiguous block of physical memory.
- Dynamic allocation and deallocation with block splitting and coalescing.
- Allocation strategies: `first_fit`, `best_fit`, `worst_fit`.
- Fragmentation statistics: utilization, external fragmentation, allocation success/failure rates.

Cache simulation:
- Two-level cache hierarchy (L1, L2).
- Direct-mapped caches, FIFO replacement.
- Write-through policy; configurable miss penalty propagation.
- Hit/miss tracking and Average Memory Access Time (AMAT).

Interactive CLI:
- Allocate, free, visualize memory layout.
- Switch allocation strategies at runtime.
- Simulate cache reads/writes and view detailed statistics.

## Project structure
memory-simulator/
├─ src/  
│  ├─ allocator/        # Allocation algorithms (first/best/worst fit)  
│  ├─ memory/           # Memory manager, block splitting/coalescing  
│  ├─ cache/            # Cache simulation and statistics  
│  ├─ cli/              # Command-line interface and parsers  
│  └─ main.cpp          # Entry point  
├─ tests/               # Sample workloads and logs (memory & cache)  
├─ docs/                # Design document and optional extensions  
├─ Makefile  
└─ README.md

## Quick start

Build
```bash
make
```

Run
```bash
./memsim
```

The simulator launches an interactive CLI. Commands are listed below.

## CLI commands & examples

General notes:
- Commands are space-separated tokens.
- Sizes/addresses are decimal by default; hex addresses (e.g., `0x10`) are accepted where noted.
- The CLI prints IDs for allocated blocks to reference when freeing.

Memory management commands
- init memory <size>  
  Initialize physical memory (bytes). Example:
  ```
  init memory 4096
  ```
- set allocator <first_fit | best_fit | worst_fit>  
  Select allocator strategy at runtime. Example:
  ```
  set allocator best_fit
  ```
- malloc <size>  
  Allocate a block and return a block id. Example:
  ```
  malloc 128
  # => Allocated block id: 1 (address: 64, size: 128)
  ```
- free <block_id>  
  Free an allocated block (coalescing applied). Example:
  ```
  free 1
  ```
- dump  
  Print a human-readable memory map (free/used blocks, addresses, sizes).
- stats  
  Print memory statistics: total memory, used, free, external fragmentation, allocation success rate.

Cache simulation commands
- cache_read <address>  
  Simulate load from the given physical address. Example:
  ```
  cache_read 0x3C
  ```
- cache_write <address>  
  Simulate store to the address (write-through policy). Example:
  ```
  cache_write 60
  ```
- cache_stats  
  Print cache statistics: accesses, hits/misses per level (L1/L2), hit rates, AMAT.

Utility commands
- help  
  List available commands and short descriptions.
- exit / quit  
  Exit the simulator.

## Testing
- tests/ contains sample workloads and expected logs for manual verification.
- Tests are executed manually through the CLI to preserve deterministic ordering and to make outputs inspectable.
- Suggested sample flows:
  - Run an allocation workload to observe fragmentation and allocator behavior.
  - Run cache access traces to measure hit/miss rates and AMAT.

## Design notes
- Cache simulation and memory allocation are intentionally decoupled for modularity and easier testing.
- Implemented features prioritize clarity and correctness over micro-optimizations.
- Optional features described in docs/:
  - Buddy allocator
  - Virtual memory / paging
  - Associative caches / configurable replacement policies

## Contributing
- Contributions welcome — open an issue to discuss features or bug reports.
- Please follow a small PR pattern: one logical change per branch with a short description and tests (where applicable).
- Code style: keep modules small and single-responsibility; add unit tests in tests/ for new behaviors.

## License & contact
- See the repository LICENSE file for license details (add one if missing).
- Author / repo: [TejasNangru](https://github.com/TejasNangru)
