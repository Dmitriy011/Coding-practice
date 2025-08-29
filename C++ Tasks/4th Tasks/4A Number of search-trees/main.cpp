#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

//* n - количество ключей  
//* res - количество различных бинарных деревьев поиска, состоящих из n вершин с ключами arr_keys


int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    long long res = 0;
    const long long mod = 123456789;

// ========= 1. Считывание задачи ========= //
    int n = 0;
    std::cin >> n;

    std::vector<long long> arr_keys(n);
    for (int i = 0; i < n; ++i)
        std::cin >> arr_keys[i];

// ========= 2. Доп переменные ========= //
    std::vector<long long> sorted_keys = arr_keys;
    std::sort(sorted_keys.begin(), sorted_keys.end());

    // DP[L][R] = количество различных BST, которые можно построить из отрезка отсортированных ключей sorted_keys[L … R].
    // Если L == R, то в отрезке один ключ → можно построить ровно одно дерево (один узел). Поэтому таблица изначально заполнена 1.
    std::vector<std::vector<long long>> DP(n, std::vector<long long>(n, 1));

// ========= 3. Решение задачи ========= //
    for (int i_key = 1; i_key < n; ++i_key)
    {
        for (int L = 0; L + i_key < n; ++L)
        {
            // i_key - это дл отрезка (R - L).
            int R = L + i_key;
            // Если в качестве корня взять самый левый эл sorted_keys[L], то в левом поддереве ничего нет(пустое дерево), а в пр поддереве остаются все эл-ы[L + 1 … R].
            DP[L][R] = DP[L + 1][R];

            // Корнем выбирается пр эл sorted_keys[R] -> Левое поддерево = все элементы [L … R-1]. Пр поддерево = пустое.
            // DP[L][R] = варианты с левым корнем + варианты с правым корнем
            if (sorted_keys[R] != sorted_keys[R - 1])
                DP[L][R] = (DP[L][R] + DP[L][R - 1]) % mod;

            // Для подотрезка [L … R] можно выбрать любой элемент sorted_keys[j_insideNode] как корень.
            // Слева остаются элементы [L … j_insideNode-1] (меньшие ключи) -> Количество вариантов = DP[L][j_root - 1]
            // Справа остаются элементы [j_insideNode+1 … R] (ключи больше или равные) -> Количество вариантов = DP[j_root + 1][R]
            // Количество деревьев = table_din[L][j_insideNode - 1] * table_din[j_insideNode + 1][R]
            // Суммируем это по всем возможным j_insideNode.
            for (int j_root = L + 1; j_root < R; ++j_root)
            {
                // Если ключ равен предыдущему, мы пропускаем этот выбор корня
                // Если в массиве есть одинаковые ключи, то разные разбиения могут давать одинаковые деревья: например, если ключи[1, 1], то дерево может быть только одно
                if (j_root > L  && sorted_keys[j_root] == sorted_keys[j_root - 1])
                    continue;

                DP[L][R] += (DP[L][j_root - 1] * DP[j_root + 1][R]) % mod;
                DP[L][R] %= mod;
            }
        }
    }

    res = DP[0][n - 1] % mod;

    std::cout << res << "\n";
}
