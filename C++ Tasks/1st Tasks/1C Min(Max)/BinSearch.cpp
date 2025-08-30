#include <algorithm>
#include <vector>

#include "BinSearch.h"

int BinarySearch(const std::vector<int>& arr_Ai, const std::vector<int>& arr_Bj)
{
//**** 1) Если A[mid] == B[mid], то max(A_i[k], B_j[k]) == A[mid] → это минимум: возвращаем mid + 1.
//**** 2 - 3) Если A[mid] > B[mid], значит max = A[mid], надо двигаться влево."V-образная" функция
//**** 2 - 3)  Если A[mid] < B[mid], значит max = B[mid], надо двигаться вправо.
//**** 4) Когда остаются два элемента L и R, выбираем тот, у которого max(A[L], B[L]) меньше.

    int L = 0;
    int R = arr_Ai.size() - 1;
    int mid = 0;
    int difference_v_mid = 0;

    while (L + 1 != R)
    {
        mid = (L + R) / 2;
        difference_v_mid = arr_Ai[mid] - arr_Bj[mid];

        // 1) 
        if (difference_v_mid == 0)
            return mid + 1;
        else
        {
            // 2 - 3)
            if (difference_v_mid > 0)
                R = mid;
            else
                L = mid;
        }
    }

    // 4) 
    if (std::max(arr_Ai[L], arr_Bj[L]) < std::max(arr_Ai[R], arr_Bj[R]))
        return L + 1;

    return R + 1;
}
