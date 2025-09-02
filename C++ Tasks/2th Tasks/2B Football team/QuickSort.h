#pragma once

#include <vector>

void QuickSort(std::vector<Player>::iterator L, std::vector<Player>::iterator R, bool (*compare_player_is2st_more) (const Player&, const Player&))
{
//**** 1) Если отрезок пустой (L == R) или из одного эл (L + 1 == R), сорт не нужно
//**** 2) Случ выбирается эл в диап [L, R) как опорный, чтобы избежать вырождения в худш случай (O(n²)).
//**** 3) L и R — это исх гр подмассива, который надо отсорт. Эти гр нужно сохр неизм, чтобы исп их при рекурсивных вызовах QuickSort.
    
    // 1) 
    if ((L == R) || (L + 1 == R))
        return;

    // 2) 
    Player pivot = *(L + rand() % (R - L));

    // 3) 
    std::vector<Player>::iterator L_it = L;
    std::vector<Player>::iterator R_it = R;

    while (L_it < R_it)
    {
        if (R_it != R)
            ++L_it;

        --R_it;

        while ((*compare_player_is2st_more)(pivot, *R_it) == true)
            --R_it;

        while ((*compare_player_is2st_more)(*L_it, pivot) == true)
            ++L_it;

        if (L_it < R_it)
            std::swap(*L_it, *R_it);
    }

    QuickSort(L, R_it + 1, (*compare_player_is2st_more));
    QuickSort(R_it + 1, R, (*compare_player_is2st_more));
}
