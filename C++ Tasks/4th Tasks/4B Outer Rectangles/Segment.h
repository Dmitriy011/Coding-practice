#pragma once

struct Segment
{
    int bound_L, bound_R;

    bool operator<(const Segment& other) const { return bound_L < other.bound_L; }
};