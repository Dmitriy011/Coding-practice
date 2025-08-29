#include <algorithm>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <random>
#include <vector>
#include <utility>

// Найти такую т.𝑦 на числовой прямой, чтобы sum(|y-xi|) -> min
// 𝑥i ​ — коорд домов жителей деревни.

// Сводится к нахождению медианы множества x1, ... 

class RandomGen
{
public:
    RandomGen(unsigned a_val, unsigned b_val) : a{ a_val }, b{ b_val } {}

    unsigned NextRand24()
    {
        curr = curr * a + b;
        return curr >> 8;
    }

    unsigned NextRand32()
    {
        unsigned tmp1_val = NextRand24();
        unsigned tmp2_val = NextRand24();

        return (tmp1_val << 8) ^ tmp2_val;
    }

private:
    unsigned curr = 0;
    unsigned a = 0;
    unsigned b = 0;
};

// Выбирает опорный эл-т (pivot) для алгоритма быстрой выборки
// Выбираем ср по знач из трёх эл-ов: L, mid и R.
std::vector<unsigned>::iterator find_pivot(std::vector<unsigned>::iterator L, std::vector<unsigned>::iterator R)
{
    std::vector<unsigned>::iterator mid = L + (R - L) / 2;  // Итератор на середину диапазона [L, R)
    --R;

    if (*mid < *L)
        std::swap(mid, L);

    if (*mid < *R)
        return mid;

    if (*L < *R)
        return R;

    return L;
}

// Делит массив вокруг pivot:
// Все элементы < pivot_value — слева
// Все ≥ pivot_value — справа
std::vector<unsigned>::iterator partition(std::vector<unsigned>::iterator L, std::vector<unsigned>::iterator R,std::vector<unsigned>::iterator pivot)
{
    unsigned pivot_value = *pivot;                      // Сохр знач опорного эл-а
    std::vector<unsigned>::iterator tmp_begin = L;      // tmp_begin — исх начало массива

    --R;                                                // R указывает на последний эл
    while (L <= R)
    {
        if (*L < pivot_value)                           // ок, двигаемся вправо
            ++L;
        else
        {
            if (pivot_value < *R)                       // ок, двигаемся влево
                --R;
            else                                        // неправильные эл-ты, надо их поменять местами
            {
                std::iter_swap(L, R);

                ++L;
                --R;
            }
        }
    }

    // L == R + 2 — означает, что цикл "перешагнул" на 2 позиции
    // L - 1 != tmp_begin — защищает от случ, когда partition затронул только один эл (в начале)
    // Если оба усло вып: Возвращается предыдущ позиция, т.к. это вероятно и есть реальная гр разделения
    // [5, 5, 5, 5, 5] -> L двигается вправо -> R == 1, L == 3 -> Возвращ L - 1 = 2
    if (L == R + 2 && L - 1 != tmp_begin)
        return L - 1;

    return L;
}

// Рекурсия 
// O(n)
unsigned find_median(std::vector<unsigned>::iterator L,
    std::vector<unsigned>::iterator R,
    std::vector<unsigned>::iterator median_it)
{
    if (R - L == 1)                                                                    // Базовый случ: массив дл 1 — это и есть медиана
        return *L;

    std::vector<unsigned>::iterator pivot_it = find_pivot(L, R);                       // Выбираем pivot
    std::vector<unsigned>::iterator partition_it = partition(L, R,  pivot_it);         // Разбиваем массив на 2ч вокруг pivot

    if (partition_it <= median_it)                                                     // Если медиана правее — ищем в правой ч
        return find_median(partition_it, R, median_it);

    return find_median(L, partition_it, median_it);                                    // Иначе — в левой ч
}

std::vector<unsigned> generate_xi(int32_t n, unsigned a, unsigned b)
{
    std::vector<unsigned> res_xi(n);

    RandomGen generator(a, b);
    for (size_t i = 0; i < res_xi.size(); ++i)
        res_xi[i] = generator.NextRand32();

    return res_xi;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

// -- Считывание задачи --//
    int32_t n = 0;
    unsigned a = 0, b = 0;
    std::cin >> n >> a >> b;

// -- Решение задачи --// 
    std::vector<unsigned> arr_x = generate_xi(n, a, b);

    std::vector<unsigned>::iterator median_it = arr_x.begin() + arr_x.size() / 2;
    int64_t median = static_cast<int64_t>(find_median(arr_x.begin(), arr_x.end(), median_it));

    // Подсчёт суммы расстояний
    int64_t sum = 0;
    for (size_t i = 0; i < arr_x.size(); ++i)
        sum += std::abs(median - arr_x[i]);

// -- Вывод решения --// 
    std::cout << sum << '\n';

    return 0;
}
