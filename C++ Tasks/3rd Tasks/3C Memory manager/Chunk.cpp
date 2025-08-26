#include <iostream>

#include "Chunk.h"


bool Chunk::operator<(const Chunk& rhs) const
{
    if (len < rhs.len)
        return true;
    if (len == rhs.len)
        return st > rhs.st;

    return false;
}

bool Chunk::operator==(const Chunk& rhs) const
{
    return (st == rhs.st) && (len == rhs.len) && (isFree == rhs.isFree) && (id == rhs.id);
}
