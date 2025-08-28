#include <iostream>

#include "MathOperations.h"


size_t GCD(size_t A, size_t B)
{
    while (B)
    {
        A %= B;
        std::swap(A, B);
    }

    return A;
}
