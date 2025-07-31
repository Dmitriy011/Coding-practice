#include <iostream>
#include <string>
#include <vector>
#include <deque>

// n - длина массива
// m - кол-во перемещений

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

// -- Считывание задачи --// 
    size_t n;
    size_t m;

    std::cin >> n;

    std::vector<int> arr(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> arr[i];

    std::cin >> m;

// -- Решение задачи --// 

    std::deque<int> arr_max;                                            // Используется монотонная очередь (Хранит значения массива в порядке убывания)
    arr_max.push_back(arr[0]);                                          // Позволяет: быстро получать max(или min) на текущ отрезке
                                                                        // arr_max.front() — всегда содержит максимум на текущем отрезке [L, R].
    size_t L = 0;
    size_t R = 0;

    // Считывание m символов и сдвиг
    for (size_t i_symbol = 0; i_symbol < m; ++i_symbol)
    {
        std::string symbol_LR;
        std::cin >> symbol_LR;

        if (symbol_LR == "L")
        {
            // Если arr[L] был  и max стоял в начале очереди, мы его удаляем
            if (!arr_max.empty() && arr_max.front() == arr[L])
                arr_max.pop_front();

            ++L;
        }
        else
        {
            if (symbol_LR == "R")
            {
                ++R;

                // Удаляем из хвоста очереди все эл-ы, которые меньше arr[R], потому что они уже не могут быть max.
                while (!arr_max.empty() && arr_max.back() < arr[R])
                    arr_max.pop_back();

                // Добавляем arr[R] в хвост
                arr_max.push_back(arr[R]);
            }
        }

        std::cout << arr_max.front() << ' ';
    }

    std::cout << '\n';

    return 0;
}
