#pragma once

#include <iostream>


class Triangle_side
{
public:
    size_t a, b, c;

    Triangle_side(size_t sideA, size_t sideB, size_t sideC) : a(sideA), b(sideB), c(sideC) {}

    bool operator == (const Triangle_side& rhs) const { return (a == rhs.a && b == rhs.b && c == rhs.c); }
};
