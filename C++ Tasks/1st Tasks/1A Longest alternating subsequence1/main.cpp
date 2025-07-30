#include <iostream>
#include <vector>

// На данном индексе последовательность возрастает или убывает.
bool Check_typeInterval(const std::vector<int>& _sequence, int _indexCurEl)
{
    if (_indexCurEl == static_cast<int>(_sequence.size()) - 1)
        return true;

    return (_sequence[_indexCurEl + 1] - _sequence[_indexCurEl] > 0);
}

int main()
{
    int n;
    int el;

    std::vector<int> arr;

    // -- Считывание чисел --//
    std::cin >> n;
    std::cin >> el;

    arr.push_back(el);
    for (int i = 1; i < n; ++i)
    {
        std::cin >> el;

        if (el != arr[static_cast<int>(arr.size()) - 1])         // Если подряд идут одинаковые числа, то в arr добавляется только одно из них.
            arr.push_back(el);                                   // (т.к. переход 5 → 5 не меняет знак, и такие элементы не участвуют в чередовании)
    }

    // -- Решение задачи --//
    std::vector<bool> subsequence(arr.size(), false);           // Булевый массив: true, если эл-т вкл в рез-щую подпоследовательность.
    subsequence[0] = true;
    std::vector<int> curIndexes;                                // Текущ "цепочка", которую пытаемся построить.
    curIndexes = { 0 };

    int16_t sign = 0;                                           // Текущ знак разности между соседними элементами: +1 — возрастает, -1 — убывает

    if (arr.size() > 1)
    {
        sign = arr[1] > arr[0] ? 1 : -1;

        curIndexes.push_back(1);
    }

    std::vector<int> interval_indexes;                          // Индексы, с которых начинаются "новые участки" подпоследовательности.
    interval_indexes.push_back(0);

    for (size_t index = 2; index < arr.size(); ++index)
    {
        if (curIndexes.size() == 1)
            sign = arr[index] > arr[index - 1] ? 1 : -1;

        if ((arr[index] - arr[index - 1]) * sign > 0)       // Если направление (sign) сохраняется, добавляем в curIndexes.
            curIndexes.push_back(index);
        else                                                // Если направление меняется, значит, происходит чередование — фикс конец предыдущ интервала (index - 1), начинаем новый.
        {
            subsequence[index - 1] = true;                  // Отмечаем последний элемент предыдущ волны, как часть итоговой подпоследоват.
            interval_indexes.push_back(index);              // Сохр, с какого места начнётся следующая волна

            curIndexes = {};                                // Сброс текущего набора curIndexes и наичнается новая волна с эл-та index
            curIndexes.push_back(index);
        }
    }

    // -- Определение, какие индексы сохранить в результате (Обработка краев и случаев с короткими последовательностями)  --//
    std::vector<int> resIndexes_subsequence{};
    if (interval_indexes.size() == 1)                       // Вся последовательность без чередований -> Выводятся первые 1–2 элемента.
    {
        resIndexes_subsequence.push_back(0);

        if (arr.size() > 1)
        {
            subsequence[1] = true;
            resIndexes_subsequence.push_back(1);
        }
    }
    else if (interval_indexes.size() > 1)                  // Есть несколько интервалов
    {
        // Добавляем последний элемент (обработаем позже) 
        subsequence[static_cast<int>(arr.size()) - 1] = true;

        for (size_t index = 1; index < interval_indexes.size(); ++index)
        {
            // Если два соседних интервала имеют одинаковый тип изменения — включаем элемент, чтобы сохранить макс длину (нужно "спасти" хотя бы один элемент,)
            if (Check_typeInterval(arr, interval_indexes[index]) ==
                Check_typeInterval(arr, interval_indexes[index - 1]))
            {
                subsequence[interval_indexes[index]] = true;
            }
        }

        // -- Формирование финального списка индексов  --// 
        for (size_t index = 0; index < subsequence.size(); ++index)
        {
            if (subsequence[index] == true)
                resIndexes_subsequence.push_back(index);
        }

        // -- Корректировка на краях интерваловов  --//  
        int tmp_intervId = 0;                                                                                       // Номер текущего интервала в interval_indexes, с которым связан текущий index
        for (size_t index = 1; index < resIndexes_subsequence.size(); ++index)
        {
            // Не вкл ли "ошибочный" элемент, стоящий на границе, и корректировка 
            // (Если элемент в resIndexes_subsequence не совпадает с тем, что стоит на границе интервала → он мог быть добавлен автоматически, и его нужно перепроверить)
            if (resIndexes_subsequence[index] != interval_indexes[tmp_intervId])
            {
                int R = resIndexes_subsequence[index];                                                              //  индекс текущего "подозрительного" элемента

                sign = arr[resIndexes_subsequence[index]] - arr[resIndexes_subsequence[index - 1]] > 0 ? 1 : -1;   // направление движения от предыдущего элемента

                if (index < static_cast<size_t>(resIndexes_subsequence.size() - 1))
                {
                    auto index_prev = resIndexes_subsequence[index - 1];
                    auto index_next = resIndexes_subsequence[index + 1];
                    // Поиск влево,  пока текущий элемент остаётся "больше" предыдущего и следующего соседа (в случае макс.)
                    while ((arr[R] - arr[index_prev]) * sign > 0 &&
                        (arr[R] - arr[index_next]) * sign > 0 &&
                        R >= interval_indexes[tmp_intervId])
                    {
                        R--;
                    }
                }
                else
                {
                    while ((arr[R] - arr[resIndexes_subsequence[index - 1]]) * sign > 0 &&
                        R >= interval_indexes[tmp_intervId])
                    {
                        R--;
                    }
                }

                resIndexes_subsequence[index] = R + 1;
                tmp_intervId++;
            }
        }
    }

    for (size_t i = 0; i < resIndexes_subsequence.size(); ++i)
        std::cout << arr[resIndexes_subsequence[i]] << " ";

    return 0;
}
