#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <string>
#include "../memory/memory_manager.h"
#include "../cache/cache_system.h"


class CommandParser {
private:
    MemoryManager* mem;
    CacheSystem cache;


public:
    CommandParser();
    void run();
};

#endif
