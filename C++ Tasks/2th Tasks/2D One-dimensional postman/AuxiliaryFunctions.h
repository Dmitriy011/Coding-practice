#pragma once

//* Выбирает опорный эл-т (pivot) для алгоритма быстрой выборки
//* Выбираем ср по знач из трёх эл-ов: L, mid и R.
std::vector<unsigned>::iterator find_pivot(std::vector<unsigned>::iterator L, std::vector<unsigned>::iterator R)
{
//* mid: итератор на середину диапазона [L, R)

    std::vector<unsigned>::iterator mid = L + (R - L) / 2;  
    --R;

    if (*mid < *L)
        std::swap(mid, L);

    if (*mid < *R)
        return mid;

    if (*L < *R)
        return R;

    return L;
}

//* Делит массив вокруг pivot: Все элементы < pivot_value — слева; Все ≥ pivot_value — справа
std::vector<unsigned>::iterator partition(std::vector<unsigned>::iterator L, std::vector<unsigned>::iterator R, std::vector<unsigned>::iterator pivot)
{
//**** 1) Сохр знач опорного эл-а

// * tmp_begin — исх начало массива
// * R - указывает на последний эл

//**** 2) ок, двигаемся вправо
//**** 3) ок, двигаемся влево. 
//**** Иначе: неправильные эл-ты, надо их поменять местами

//**** 5) L == R + 2 — означает, что цикл "перешагнул" на 2 позиции
//**** L - 1 != tmp_begin — защищает от случ, когда partition затронул только один эл (в начале)
//**** Если оба усло вып: Возвращается предыдущ позиция, т.к. это вероятно и есть реальная гр разделения
//**** [5, 5, 5, 5, 5] -> L двигается вправо -> R == 1, L == 3 -> Возвращ L - 1 = 2

    // 1) 
    unsigned pivot_value = *pivot;
    std::vector<unsigned>::iterator tmp_begin = L;       

    --R;                                                
    while (L <= R)
    {
    // 2) 
        if (*L < pivot_value)                           
            ++L;
        else
        {
    // 3) 
            if (pivot_value < *R)                     
                --R;
            else    
            {
                std::iter_swap(L, R);

                ++L;
                --R;
            }
        }
    }

    // 5) 
    if (L == R + 2 && L - 1 != tmp_begin)
        return L - 1;

    return L;
}

