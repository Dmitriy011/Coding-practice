#pragma once

//* Выбирает опорный эл-т (pivot) для алгоритма быстрой выборки
//* Выбираем ср по знач из трёх эл-ов: L, mid и R.
std::vector<unsigned>::iterator find_pivot(std::vector<unsigned>::iterator L, std::vector<unsigned>::iterator R);

//* Делит массив вокруг pivot: Все элементы < pivot_value — слева; Все ≥ pivot_value — справа
std::vector<unsigned>::iterator partition(std::vector<unsigned>::iterator L, std::vector<unsigned>::iterator R, std::vector<unsigned>::iterator pivot);

