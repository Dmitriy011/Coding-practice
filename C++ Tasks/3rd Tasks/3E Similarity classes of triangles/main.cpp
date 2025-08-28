#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

#include "MathOperations.h"
#include "Triangle_side.h"

//* n Треугольников со сторонами a, b, c

//* 2 треуг подобны, если их стороны пропорциональны: (a, b, c) и (x, y, z) существует такое число k, что: a = k * x,  b = k * y,  c = k * z


size_t Hash_func(size_t prime1_val, size_t prime2_val, size_t n, Triangle& cur_t)
{
    size_t tmp1_val = cur_t.A % n;
    size_t tmp2_val = cur_t.B % n * prime1_val % n;
    size_t tmp3_val = cur_t.C % n * prime2_val % n;

    size_t res = (tmp1_val + tmp2_val + tmp3_val) % n;

    return res;
}

size_t Add_similiarTriangle(size_t& res, Triangle& cur_t, std::vector<std::vector<Triangle>>& triangles_side)
{
    size_t hash_val = Hash_func(101, 103, triangles_side.size(), cur_t);

    // 1. Если бакет пустой - добавляем
    // 2. Иначе (если не пустой) - проверяем, есть ли такой же треугольник.
    if (triangles_side[hash_val].empty())
    {
        triangles_side[hash_val].push_back(cur_t);
        res++;
    }
    else
    {
        bool isFound = false;
        for (auto& t : triangles_side[hash_val])
        {
            if (t == cur_t)
            {
                isFound = true;
                break;
            }
        }

        // 2.1. Если ещё не встречался -  добавляем и увеличиваем счётчик классов.
        if (!isFound)
        {
            triangles_side[hash_val].push_back(cur_t);
            res++;
        }
    }

    return res;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

// ========= 1. Считывание задачи ========= //
    size_t res = 0;

    size_t n;

    size_t A, B, C;
    std::cin >> n;

    std::vector<std::vector<Triangle>> triangles_sides(n);

    for (size_t No_triangle = 0; No_triangle < n; ++No_triangle)
    {
        std::cin >> A >> B >> C;

// ========= 2.  Сортируем стороны треуг, чтобы гарантировать (A ≤ B ≤ C) ========= //
        if (A > B)
            std::swap(A, B);

        if (A > C)
            std::swap(A, C);

        if (B > C)
            std::swap(B, C);

// ========= 3. Делим стороны на их НОД, чтобы привести к каноническому виду ========= //
// * Все подобные треугольники сведутся к одинаковой тройке целых чисел
        int gcd_val = GCD(A, GCD(B, C));
        Triangle tmp_triangle(A / gcd_val, B / gcd_val, C / gcd_val);

// ========= 4. Подсчет классов подобия ========= //
        Add_similiarTriangle(res, tmp_triangle, triangles_sides);
    }

    std::cout << res << '\n';
}
