#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <utility>

#include "BinaryIndexedTree.h"

// Если бы мы после кажд операции брали подмассив [L,R], сортировали его и выбирали k-й эл — это было бы O(n log n) на кажд запрос
// УЛУЧШЕНИЕ: 
// После кажд операции меняется только 1 эл окна:
// * 1) Каждому числу сопоставляем индекс от 0 до n-1 (ранг по величине)
// * 2) В BIT храним: сколько раз каждая "сжатая координата" встречается в текущем окне [L,R].

// Decision 1-4.
// * a = [40, 10, 30]
// * после сортировки : [(10, 1), (30, 2), (40, 0)]
// * sorted_positions = [2, 0, 1]


std::vector<int> Decision(const std::string& requests_str, const int size_curArr, const std::vector<int>& cur_arr, const int k)
{
    // 1. Создаётся массив пар (val, index)
    std::vector<std::pair<int, int>> numbers_indexed;

    // 2. Заполняем массив пар
    for (size_t i = 0; i < cur_arr.size(); ++i)
        numbers_indexed.push_back(std::make_pair(cur_arr[i], i));

    // 3. Сортируем по значению: numbers_indexed[i] хранит i-й по величине эл и его исх pos.
    std::sort(numbers_indexed.begin(), numbers_indexed.end());

    // 4. sorted_positions[i] = место числа arr[i] в отсортированном массиве.
    std::vector<size_t> sorted_positions(size_curArr, 0);

    for (size_t i = 0; i < numbers_indexed.size(); ++i)
        sorted_positions[numbers_indexed[i].second] = i;

    // 5. Создаём BIT размером n и доб 1ый эл 
    // i: arr[i] =  numbers_indexed[sorted_positions[i]].first
    BinaryIndexedTree BIT(size_curArr);
    BIT.Add(sorted_positions[0]);

    size_t L = 0, R = 0;

    std::vector<int> res;

    // 6. Выполнение запросов: 
    for (size_t No_req = 0; No_req < requests_str.size(); ++No_req)
    {
        // 6.1. Удаляем из BIT число, на которое указывал L, и двигаем L вправо.
        // Или Двигаем R вправо и добавляем в BIT новый элемент.
        if (requests_str[No_req] == 'L')
        {
            // Уменьшаем частоту числа arr[sorted_positions[L]]
            BIT.Remove(sorted_positions[L]);
            ++L;
        }
        else
        {
            if (requests_str[No_req] == 'R')
            {
                ++R;

                // Увеличиваем частоту числа arr[sorted_positions[R]].
                BIT.Add(sorted_positions[R]);
            }
        }

        // 6.2. Возвращ индекс в отсортирован массиве (Если эл-ов < k, то вернёт отрицат число.)
        int stat = BIT.GetStatistics(k);

        if (stat < 0)
            res.push_back(-1);
        else
        {
            int old_index = numbers_indexed[stat].second;
            res.push_back(cur_arr[old_index]);
        }
    }

    return res;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    int n, m, k;

    std::cin >> n;
    std::cin >> m;
    std::cin >> k;

    std::vector<int> numbers(n);
    std::string requests_str;

    for (size_t i = 0; i < n; ++i)
        std::cin >> numbers[i];
    std::cin >> requests_str;

    std::vector<int> result = Decision(requests_str, n, numbers, k);

    for (size_t i = 0; i < result.size(); ++i)
        std::cout << result[i] << "\n";
}

