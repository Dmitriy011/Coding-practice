#pragma once

#include <iostream>

struct Chunk
{
    int st;
    int len;
    int id;         // Номер позиции блока в куче
    bool isFree;

    Chunk(int _st = 0, int _len = 0, bool _isFree = false, int _id = 0) : st(_st), len(_len), id(_id), isFree(_isFree) {}

    bool operator <(const Chunk& rhs) const;
    bool operator >(const Chunk& rhs) const { return rhs < *this; }

    bool operator ==(const Chunk& rhs) const;
};
