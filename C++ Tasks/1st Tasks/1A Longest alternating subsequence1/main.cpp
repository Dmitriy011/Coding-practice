#include <iostream>
#include <vector>

//* На данном индексе последовательность возрастает или убывает.
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

// ========= 1. Считывание задачи ========= //

//* Если подряд идут одинаковые числа, то в arr добавляется только одно из них
//* Т.к. переход 5 → 5 не меняет знак, и такие элементы не участвуют в чередовании)
    std::cin >> n;
    std::cin >> el;

    arr.push_back(el);
    for (int i = 1; i < n; ++i)
    {
        std::cin >> el;
        if (el != arr[static_cast<int>(arr.size()) - 1])
            arr.push_back(el);
    }

// ========= 2. Решение задачи ========= //

//* subsequence: Булевый массив: true, если эл-т вкл в рез-щую подпослед.
//* curIndexes: Текущ "цепочка", которую пытаемся построить.
//* sign: Текущ знак разности между соседними эл-ми: +1возрастает, -1 убывает
//* interval_indexes: Индексы, с которых начин "новые участки" подпоследоват.

    std::vector<bool> subsequence(arr.size(), false);
    subsequence[0] = true;
    std::vector<int> curIndexes; 
    curIndexes = { 0 };

    int16_t sign = 0;

    if (arr.size() > 1)
    {
        sign = arr[1] > arr[0] ? 1 : -1;

        curIndexes.push_back(1);
    }

    std::vector<int> interval_indexes;
    interval_indexes.push_back(0);

// ================== //

//* Если направление (sign) сохр, добавляем в curIndexes.
//* Иначе (если направление меняется): значит, происходит чередование — фикс конец предыдущ интервала (i - 1), начинаем новый:
//**** subsequence[i - 1] = true; Отмечаем послед эл предыдущ волны, как часть итог подпоследоват.
//**** interval_indexes.push_back(i); Сохр, с какого места начнётся следующ волна
//**** curIndexes = {}; Сброс текущ набора curIndexes и начин новая волна с эл-та i

    for (size_t i = 2; i < arr.size(); ++i)
    {
        if (curIndexes.size() == 1)
            sign = arr[i] > arr[i - 1] ? 1 : -1;

        if ((arr[i] - arr[i - 1]) * sign > 0)
            curIndexes.push_back(i);
        else 
        {
            subsequence[i - 1] = true;
            interval_indexes.push_back(i);

            curIndexes = {};
            curIndexes.push_back(i);
        }
    }

    std::vector<int> resIndexes_subsequence{};

// ================== //

//* Если вся последовательность без чередований -> Выводятся первые 1–2 элемента.
//* Иначе если (Есть несколько интервалов)
//**** 1) subsequence[static_cast<int>(arr.size()) - 1] = true; Добавляем последний элемент (обработаем позже)
//**** 2) Если 2 соседн интервала имеют одинак тип изм — вкл эл, чтобы сохр макс длину (нужно "спасти" хотя бы один эл)
//**** 3) Формирование финального списка индексов
//**** 4) Корректировка на краях интерваловов 
//**** 5) tmp_intervId = 0; Номер текущ интервала в interval_indexes, с которым связан текущий i
//**** 6) Не вкл ли "ошибочный" эл, стоящий на гр, и корр (Если эл в resIndexes_subsequence не совп с тем, что стоит на границе интерв → он мог быть доб автоматич, и его нужно перепровер)
//**** 7) int R = resIndexes_subsequence[i];  индекс текущ "подозрительного" эл
//**** 8) sign направление движения от предыдущ эл
//**** 9) Поиск влево, пока текущ эл остаётся "больше" предыдущ и следующ соседа (в случае макс.)

    if (interval_indexes.size() == 1)
    {
        resIndexes_subsequence.push_back(0);

        if (arr.size() > 1)
        {
            subsequence[1] = true;
            resIndexes_subsequence.push_back(1);
        }
    }
    else if (interval_indexes.size() > 1)
    {
        // 1)
        subsequence[static_cast<int>(arr.size()) - 1] = true;

        for (size_t i = 1; i < interval_indexes.size(); ++i)
        {
        // 2) 
            if (Check_typeInterval(arr, interval_indexes[i]) == Check_typeInterval(arr, interval_indexes[i - 1]))
                subsequence[interval_indexes[i]] = true;
        }

        // 3)
        for (size_t i = 0; i < subsequence.size(); ++i)
        {
            if (subsequence[i] == true)
                resIndexes_subsequence.push_back(i);
        }

        // 4) 
        // 5) 
        int tmp_intervId = 0;
        for (size_t i = 1; i < resIndexes_subsequence.size(); ++i)
        {
        // 6) 
            if (resIndexes_subsequence[i] != interval_indexes[tmp_intervId])
            {
        // 7) 
                int R = resIndexes_subsequence[i];

        // 8)
                sign = arr[resIndexes_subsequence[i]] - arr[resIndexes_subsequence[i - 1]] > 0 ? 1 : -1;

                if (i < static_cast<size_t>(resIndexes_subsequence.size() - 1))
                {
                    auto i_prev = resIndexes_subsequence[i - 1];
                    auto i_next = resIndexes_subsequence[i + 1];
        // 9)
                    while ((arr[R] - arr[i_prev]) * sign > 0 && (arr[R] - arr[i_next]) * sign > 0 && R >= interval_indexes[tmp_intervId])
                        R--;
                }
                else
                {
                    while ((arr[R] - arr[resIndexes_subsequence[i - 1]]) * sign > 0 && R >= interval_indexes[tmp_intervId])
                        R--;
                }

                resIndexes_subsequence[i] = R + 1;
                tmp_intervId++;
            }
        }
    }

// ========= 3. Вывод ответа ========= //
    for (size_t i = 0; i < resIndexes_subsequence.size(); ++i)
        std::cout << arr[resIndexes_subsequence[i]] << " ";

    return 0;
}
