#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

// n количество массивов A_i
// m количество массивов B_i
// q запросов (i, j) -> q ответов таких k: max(Aik, Bjk) минимален

// Бинарный поиск ищет точку минимума этой функции f(k) = max(A[k], B[k]) 
// "V-образная" функция.
int bin_search(const std::vector<int>& arr_Ai, const std::vector<int>& arr_Bj)
{
    int L = 0;
    int R = arr_Ai.size() - 1;
    int mid = 0;
    int difference_v_mid = 0;

    while (L + 1 != R)
    {
        mid = (L + R) / 2;
        difference_v_mid = arr_Ai[mid] - arr_Bj[mid];

        if (difference_v_mid == 0)      // Если A[mid] == B[mid], то max(A_i[k], B_j[k]) == A[mid] → это минимум: возвращаем mid + 1.
            return mid + 1;
        else
        {
            if (difference_v_mid > 0)   // Если A[mid] > B[mid], значит max = A[mid], надо двигаться влево.
                R = mid;
            else                        // Если A[mid] < B[mid], значит max = B[mid], надо двигаться вправо.
                L = mid;
        }
    }

    // Когда остаются два элемента L и R, выбираем тот, у которого max(A[L], B[L]) меньше.
    if (std::max(arr_Ai[L], arr_Bj[L]) < std::max(arr_Ai[R], arr_Bj[R]))
        return L + 1;

    return R + 1;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);


    // -- Считывание задачи --//
    int n = 0;
    int m = 0;
    int l = 0;

    std::cin >> n >> m >> l;

    std::vector<std::vector<int>> arrays_a(n, std::vector<int>(l)); // Вектор векторов с n строками длины l, храняющих A_i для всех i
    std::vector<std::vector<int>> arrays_b(m, std::vector<int>(l)); // Вектор векторов с m строками длины l, храняющих B_i для всех i

    for (int i = 0; i < n; ++i)
    {
        for (int No_el = 0; No_el < l; ++No_el)
            std::cin >> arrays_a[i][No_el];
    }

    for (int j = 0; j < m; ++j)
    {
        for (int No_el = 0; No_el < l; ++No_el)
            std::cin >> arrays_b[j][No_el];
    }

    int q = 0;
    std::cin >> q;

    int i = 0;
    int j = 0;

    std::vector<int> k_results(q);
    for (int No_request = 0; No_request < q; ++No_request)
    {
        std::cin >> i >> j;

        // -- Решение задачи для считанных в q-ом запросе (i, j) -- //
        if (arrays_a[i - 1][0] >= arrays_b[j - 1][0])                   // Если в начале A_i[0] ≥ B_j[0], значит уже на k=1:max(A_i[0], B_j[0]) = A_i[0]
        {                                                               // и с ростом A_i и убыванием B_j max(...) только увеличится.Так что ответ — k = 1.
            k_results[No_request] = 1;
            continue;
        }
        else                                                            // Аналогично предыдущ случаю
        {
            if (arrays_b[j - 1][l - 1] >= arrays_a[i - 1][l - 1])
            {
                k_results[No_request] = l;
                continue;
            }
        }

        k_results[No_request] = bin_search(arrays_a[i - 1], arrays_b[j - 1]);   // Иначе — бинарный поиск: ищет такое k, что max(A_i[k], B_j[k]) минимален.
    }

    // -- Вывод ответа --//
    for (int No_request = 0; No_request < q; ++No_request)
        std::cout << k_results[No_request] << "\n";

    return 0;
}
