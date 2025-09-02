#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <functional>

#include "PriorityQueue.h"


//* n - количество массивов
//* m - длина последовательности

//* Ограничения:
// 1) Время: O(mn log n) — типичная сложность для k - way merge с использованием кучи.
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

// ========= 1. Считывание задачи ========= // 

//* countProcessed: Вектор счётчиков: сколько эл-ов уже обработано в каждой строке.
//* arrs: Двумерный вектор: n строк по m элементов.

    size_t n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> arrs(n, std::vector<int>(m));
    for (size_t i_arr = 0; i_arr < n; ++i_arr)
    {
        for (size_t j_el = 0; j_el < m; ++j_el)
            std::cin >> arrs[i_arr][j_el];
    }

// ========= 2. Решение задачи ========= // 

//* countProcessed: Вектор счётчиков: сколько эл-ов уже обработано в каждой строке.

//**** 1) Создаём min-heap. В ней храним пары {знач, номер массива}.
//**** 2) Кладём 1ые эл-ты всех n массивов в кучу.
//**** 3) Пока куча не пуста — продолж извлеч миним эл-ов.
//**** 4) Выводим наим знач из кучи (всегда на heap.top()).
//**** 5) Получаем номер массива, из котор был эл.
//**** 6) Ув счётчик обработанных эл-ов в этом массиве.
//**** 7) Если в том массиве ещё остались эл-ты — кладём след эл в кучу.

    std::vector<size_t> countProcessed(n, 0);

    // 1) 
    PriorityQueue<std::pair<int, size_t>, std::greater<std::pair<int, size_t>>> heap;
    // 2) 
    for (size_t i_arr = 0; i_arr < n; ++i_arr)
    {
        std::pair<int, size_t> val = std::make_pair(arrs[i_arr][countProcessed[i_arr]], i_arr);
        heap.push(val);
    }

    // 3) 
    while (!heap.isEmpty()) 
    {
        //4) 
        std::cout << heap.top().first << ' ';

        //5) 
        size_t i_curArr = heap.top().second;
        heap.pop();
        //6) 
        ++countProcessed[i_curArr];

        //7) 
        bool isProcessed = isProcessedCurArr(countProcessed[i_curArr], m);
        if (isProcessed)
        {
            std::pair<int, size_t> val = std::make_pair(arrs[i_curArr][countProcessed[i_curArr]], i_curArr);
            heap.push(val);
        }
    }

    std::cout << '\n';

    return 0;
}
