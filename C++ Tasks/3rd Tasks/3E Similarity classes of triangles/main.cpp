#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

#include "MathOperations.h"
#include "Triangle_side.h"


size_t hash_func(size_t prime1_val, size_t prime2_val, size_t n, Triangle_side& triangle)
{
    size_t tmp1_val = triangle.a % n;
    size_t tmp2_val = triangle.b % n * prime1_val % n;
    size_t tmp3_val = triangle.c % n * prime2_val % n;

    size_t res = (tmp1_val + tmp2_val + tmp3_val) % n;

    return res;
}

size_t add_similiarTriangle(size_t& res, Triangle_side& triangle, std::vector<std::vector<Triangle_side>>& triangles_side)
{
    size_t hash = hash_func(101, 103, triangles_side.size(), triangle);

    if (triangles_side[hash].empty())
    {
        triangles_side[hash].push_back(triangle);
        res++;
    }
    else
    {
        bool is_similarTriangle = false;

        for (size_t No_bucket = 0; No_bucket < triangles_side[hash].size(); ++No_bucket)
        {
            if (triangles_side[hash][No_bucket] == triangle)
            {
                is_similarTriangle = true;
                break;
            }
        }

        if (is_similarTriangle == false)
        {
            triangles_side[hash].push_back(triangle);
            res++;
        }
    }

    return res;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    size_t res = 0;

    size_t n;

    size_t a, b, c;
    std::cin >> n;

    std::vector<std::vector<Triangle_side>> triangles_sides(n);

    for (size_t No_triangle = 0; No_triangle < n; ++No_triangle)
    {
        std::cin >> a >> b >> c;

        if (a > b)
            std::swap(a, b);

        if (a > c)
            std::swap(a, c);

        if (b > c)
            std::swap(b, c);

        int gcd_val = gcd(a, gcd(b, c));
        a = a / gcd_val;
        b = b / gcd_val;
        c = c / gcd_val;

        Triangle_side tmp_triangle(a, b, c);

        add_similiarTriangle(res, tmp_triangle, triangles_sides);
    }

    std::cout << res << '\n';
}
