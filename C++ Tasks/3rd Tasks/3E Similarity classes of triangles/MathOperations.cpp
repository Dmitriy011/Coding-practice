#include <iostream>

#include "MathOperations.h"


size_t gcd(size_t a, size_t b)
{
    while (b)
    {
        a %= b;
        std::swap(a, b);
    }

    return a;
}
