#include <algorithm>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <random>
#include <vector>
#include <utility>

#include "RandomGen.h"
#include "AuxiliaryFunctions.h"

//* Найти такую т.𝑦 на числовой прямой, чтобы sum(|y-xi|) -> min
//* 𝑥i ​ — коорд домов жителей деревни.

//* Сводится к нахождению медианы множества x1, ... 

//* Рекурсия O(n)
unsigned find_median(std::vector<unsigned>::iterator L, std::vector<unsigned>::iterator R, std::vector<unsigned>::iterator median_it)
{ 
//**** 1) Базовый случ: массив дл 1 — это и есть медиана
//**** 2) Выбираем pivot
//**** 3) Разбиваем массив на 2ч вокруг pivot
//**** 4) Если медиана правее — ищем в правой ч
//**** 5) Иначе — в левой ч

    // 1) 
    if (R - L == 1)                                                                     
        return *L;

    // 2)
    std::vector<unsigned>::iterator pivot_it = find_pivot(L, R);                        
    // 3) 
    std::vector<unsigned>::iterator partition_it = partition(L, R,  pivot_it);          
    // 4) 
    if (partition_it <= median_it)                                                     
        return find_median(partition_it, R, median_it);

    // 5) 
    return find_median(L, partition_it, median_it);                                     
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

// ========= 1. Считывание задачи ========= // 
    int32_t n = 0;
    unsigned a = 0, b = 0;
    std::cin >> n >> a >> b;

// ========= 2. Решение задачи ========= // 

//**** 1) Подсчёт суммы расстояний

    std::vector<unsigned> arr_x = generate_xi(n, a, b);

    std::vector<unsigned>::iterator median_it = arr_x.begin() + arr_x.size() / 2;
    int64_t median = static_cast<int64_t>(find_median(arr_x.begin(), arr_x.end(), median_it));

    // 1) 
    int64_t sum = 0;
    for (size_t i = 0; i < arr_x.size(); ++i)
        sum += std::abs(median - arr_x[i]);

// ========= 3. Вывод решения ========= // 
    std::cout << sum << '\n';

    return 0;
}
