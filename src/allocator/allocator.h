#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <list>
#include "block.h"

class Allocator {
public:
    virtual ~Allocator() {}
    virtual std::list<Block>::iterator
    findBlock(std::list<Block>& blocks, size_t size) = 0;
};

#endif
