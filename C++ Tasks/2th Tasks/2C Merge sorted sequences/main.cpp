#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <functional>

#include "PriorityQueue.h"


// n- количество массивов
// m - длиан последовательности

//Ограничения:
// 1)Время: O(mn log n) — типичная сложность для k - way merge с использованием кучи.
// 2) Память: O(mn) — можно хранить все элементы (это и есть входные данные), но работать эффективно.

// Проверяет, остались ли ещё элементы в данной последовательности: true, если есть что читать.
bool isProcessedCurArr(const size_t countProcessed_inArray, const size_t m_sizeArr)
{
    return countProcessed_inArray < m_sizeArr;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

// -- Считывание задачи --// 
    size_t n;
    size_t m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> arrs(n, std::vector<int>(m));                  // Двумерный вектор: n строк по m элементов.
    for (size_t i_arr = 0; i_arr < n; ++i_arr)
    {
        for (size_t j_el = 0; j_el < m; ++j_el)
            std::cin >> arrs[i_arr][j_el];
    }

// -- Решение задачи --// 

    std::vector<size_t> countProcessed(n, 0);                                   // Вектор счётчиков: сколько эл-ов уже обработано в каждой строке.

    // Создаём min-heap. В ней храним пары {знач, номер массива}.
    PriorityQueue<std::pair<int, size_t>, std::greater<std::pair<int, size_t>>> heap;
    // Кладём 1ые эл-ты всех n массивов в кучу.
    for (size_t i_arr = 0; i_arr < n; ++i_arr)
    {
        std::pair<int, size_t> val = std::make_pair(arrs[i_arr][countProcessed[i_arr]], i_arr);
        heap.push(val);
    }

    while (!heap.isEmpty())                                                    // Пока куча не пуста — продолж извлеч миним эл-ов.
    {
        std::cout << heap.top().first << ' ';                                  // Выводим наим знач из кучи (всегда на heap.top()).

        size_t i_curArr = heap.top().second;                                   // Получаем номер массива, из котор был эл.
        heap.pop();
        ++countProcessed[i_curArr];                                            // Ув счётчик обработанных эл-ов в этом массиве.

        bool isProcessed = isProcessedCurArr(countProcessed[i_curArr], m);     // Если в том массиве ещё остались эл-ты — кладём след эл в кучу.
        if (isProcessed)
        {
            std::pair<int, size_t> val = std::make_pair(arrs[i_curArr][countProcessed[i_curArr]], i_curArr);
            heap.push(val);
        }
    }

    std::cout << '\n';

    return 0;
}
