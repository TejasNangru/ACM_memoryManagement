#include "command_parser.h"
#include <iostream>
#include <sstream>

#include "../allocator/first_fit.cpp"
#include "../allocator/best_fit.cpp"
#include "../allocator/worst_fit.cpp"
#include "../cache/cache_system.h"

CommandParser::CommandParser() : mem(nullptr) {}

void CommandParser::run() {
    std::string line;

    std::cout << "Memory Management Simulator\n";
    std::cout << "Type 'exit' to quit\n";

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, line);

        if (line.empty())
            continue;

        std::stringstream ss(line);
        std::string command;
        ss >> command;

        // EXIT
        if (command == "exit") {
            break;
        }

        // INIT MEMORY
        else if (command == "init") {
            std::string word;
            size_t size;
            ss >> word >> size;   // init memory 1024

            if (word != "memory") {
                std::cout << "Usage: init memory <size>\n";
                continue;
            }

            delete mem;
            mem = new MemoryManager(size);
            std::cout << "Initialized memory of size " << size << "\n";
        }

        // SET ALLOCATOR
        else if (command == "set") {
            std::string type, algo;
            ss >> type >> algo;   // set allocator first_fit

            if (!mem) {
                std::cout << "Memory not initialized\n";
                continue;
            }

            if (type != "allocator") {
                std::cout << "Usage: set allocator <first_fit|best_fit|worst_fit>\n";
                continue;
            }

            if (algo == "first_fit")
                mem->setAllocator(new FirstFitAllocator());
            else if (algo == "best_fit")
                mem->setAllocator(new BestFitAllocator());
            else if (algo == "worst_fit")
                mem->setAllocator(new WorstFitAllocator());
            else {
                std::cout << "Unknown allocator\n";
                continue;
            }

            std::cout << "Allocator set to " << algo << "\n";
        }

        // MALLOC
        else if (command == "malloc") {
            size_t size;
            ss >> size;

            if (!mem) {
                std::cout << "Memory not initialized\n";
                continue;
            }

            mem->allocate(size);
        }

        // FREE
        else if (command == "free") {
            int id;
            ss >> id;

            if (!mem) {
                std::cout << "Memory not initialized\n";
                continue;
            }

            mem->freeBlock(id);
        }

        // DUMP
        else if (command == "dump") {
            if (!mem) {
                std::cout << "Memory not initialized\n";
                continue;
            }

            mem->dumpMemory();
        }

        // MEMORY STATS
        else if (command == "stats") {
            if (!mem) {
                std::cout << "Memory not initialized\n";
                continue;
            }

            mem->printStats();
        }

        // CACHE READ
        else if (command == "cache_read") {
            size_t addr;
            ss >> addr;
            cache.read(addr);
        }

        // CACHE WRITE
        else if (command == "cache_write") {
            size_t addr;
            ss >> addr;
            cache.write(addr);
        }

        // CACHE STATS
        else if (command == "cache_stats") {
            cache.printStats();
        }

        else {
            std::cout << "Unknown command\n";
        }
    }

    delete mem;
}
