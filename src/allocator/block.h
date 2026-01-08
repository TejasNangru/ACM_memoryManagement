#ifndef BLOCK_H
#define BLOCK_H

#include <cstddef>

struct Block {
    size_t start;   // starting address
    size_t size;    // size of block
    bool free;      // free or allocated
    int id;         // allocation id (-1 if free)

    Block(size_t s, size_t sz)
        : start(s), size(sz), free(true), id(-1) {}
};

#endif
