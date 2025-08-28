#pragma once

#include <iostream>

//* A, B, C - длины сторон треугольника

class Triangle
{
public:
    size_t A, B, C;

    Triangle(size_t _A, size_t B, size_t C) : A(_A), B(B), C(C) {}

    bool operator == (const Triangle& rhs) const { return (A == rhs.A && B == rhs.B && C == rhs.C); }
};
