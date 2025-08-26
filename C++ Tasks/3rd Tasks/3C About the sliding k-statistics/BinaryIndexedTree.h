#pragma once

#include "iostream"
#include <vector>

class BinaryIndexedTree
{
public:
    explicit BinaryIndexedTree(int _len);

    void Add(int el) { Inc(el, 1); }

    void Remove(int el) { Inc(el, -1); }

    int GetStatistics(int k);

private:
    int Prefix_Si(int i);
    void Inc(int o, int delta);

    int len;
    std::vector<int> prefix_freq;
};

// * Массив: [40, 10, 30] → numbers_indexes: {10 1; 30 2; 40 0} → sorted_pos [2,0,1]
// * Начальное окно[L, R] = [0, 0] → только элемент 40 (sorted_pos = 2)
// freq_indexes = [0, 0, 1]: в позиции 2 один элемент

// * Выполняем операцию R → добавляем 10 (ранг 0)
// freq_indexes = [1, 0, 2]:  теперь в окне [40 и 10]

// * Выполняем операцию L → удаляем 40 (sorted_pos = 2)
// freq_indexes = [1, 0, 0]  // теперь в окне только [10]

