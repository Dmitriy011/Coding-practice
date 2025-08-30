#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

#include "BinSearch.h"


//* n количество массивов A_i
//* m количество массивов B_i
//* q запросов (i, j) -> q ответов таких k: max(Aik, Bjk) минимален

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

// ========= 1. Считывание задачи ========= //
    int n = 0;
    int m = 0;
    int l = 0;

    std::cin >> n >> m >> l;

    std::vector<std::vector<int>> arr_A(n, std::vector<int>(l)); // Вектор векторов с n строками длины l, храняющих A_i для всех i
    std::vector<std::vector<int>> arr_B(m, std::vector<int>(l)); // Вектор векторов с m строками длины l, храняющих B_i для всех i

    for (int i = 0; i < n; ++i)
    {
        for (int No_el = 0; No_el < l; ++No_el)
            std::cin >> arr_A[i][No_el];
    }

    for (int i = 0; i < m; ++i)
    {
        for (int No_el = 0; No_el < l; ++No_el)
            std::cin >> arr_B[i][No_el];
    }

    int q = 0;
    std::cin >> q;

    int i = 0, j = 0;

    std::vector<int> k_results(q);
    for (int i_request = 0; i_request < q; ++i_request)
    {
        std::cin >> i >> j;

// ========= 2. Решение задачи для считанных в q-ом запросе (i, j) ========= //

//**** 1) Если в начале A_i[0] ≥ B_j[0], значит уже на k=1:max(A_i[0], B_j[0]) = A_i[0]. И с ростом A_i и убыванием B_j max(...) только увеличится.Так что ответ — k = 1.
//**** 2) Аналогично предыдущ случаю
//**** 3) Иначе — бинарный поиск: ищет такое k, что max(A_i[k], B_j[k]) минимален.

        //1) 
        if (arr_A[i - 1][0] >= arr_B[j - 1][0])
        {
            k_results[i_request] = 1;
            continue;
        }
        else
        {
        // 2) 
            if (arr_B[j - 1][l - 1] >= arr_A[i - 1][l - 1])
            {
                k_results[i_request] = l;
                continue;
            }
        }

        // 3) 
        k_results[i_request] = BinarySearch(arr_A[i - 1], arr_B[j - 1]);
    }

// ========= 3. Вывод ответа ========= //    
    for (int i = 0; i < q; ++i)
        std::cout << k_results[i] << "\n";

    return 0;
}
