#include <iostream>
#include <iomanip>
#include <vector>

//* Дуча - бинарное дерево, в узлах которого хранятся пары (x,y), где x — это ключ, а y — это приоритет: 
//* Является двоичным деревом поиска по x и кучей по y

//* Ключи фиксированы: (1 , 𝑖_1), (2 , 𝑖_2) , … , (𝑛, 𝑖_𝑛):
//* где (𝑖_1 , … , 𝑖_𝑛) — случайная перестановка чисел от 1 до n.

//* Пусть p[n][h] — вероятность, что у дерева из n вершин высота = h.
//* Базовые случаи: p[0][0] = 1 (пустое дерево высоты 0), p[1][0] = 1 (одно дерево из одной вершины имеет высоту 0), p[1][1] = 0 (высота не может быть 1).
//* Для n > 1: корень выбирается случайно (равновероятно среди всех вершин).

//* Пусть в левом поддереве i вершин, в правом n − i − 1.
//* Высота дерева h, если максимум из высот поддеревьев равен h − 1.


// Случай 1: одно поддерево высоты h-1, другое < h-1
long double Calculate_p1(size_t count_v, size_t h, std::vector<std::vector<long double>>& p)
{
    long double p1 = 0.0;

    for (size_t i = 0; i <= count_v - 1; ++i)
    {
        // Суммируем все случаи, когда 2ое поддерево имеет высоту j, где j = 0, … ,h − 2.
        for (size_t j = 0; j < h - 1; ++j)
            p1 += 2.0 * p[i][h - 1] * p[count_v - i - 1][j];
    }

    return p1;
}

// Cлучай 2: оба поддерева высоты h-1
long double Calculate_p2(size_t count_v, size_t h, std::vector<std::vector<long double>>& p)
{
    long double p2 = 0.0;

    for (size_t i = 0; i <= count_v - 1; ++i)
        p2 += p[i][h - 1] * p[count_v - i - 1][h - 1];

    return p2;
}

long double Calculate_probabilities(size_t n,  size_t height, std::vector<std::vector<long double>>& p)
{
    long double temp_probability = 0.0;
    for (size_t count_v = 2; count_v <= n; ++count_v)
    {
        for (size_t h = 1; h <= height; ++h)
        {
            temp_probability = 0.0 + Calculate_p1(count_v, h, p) + Calculate_p2(count_v, h, p);

            // Вероятность, что высота дерева из count_v вершин равна tmp_h.
            // Усреднение по выбору корня
            p[count_v][h] = temp_probability / count_v;
        }
    }

    return p[n][height];
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

// ========= 1. Считывание задачи ========= //
    size_t n, h;
    std::cin >> n >> h;

    std::vector<std::vector<long double>> probability_vec(101, std::vector<long double>(101, 0.0));

    if (h >= n)
    {
        std::cout << std::setprecision(5) << 0 << '\n';

        return 0;
    }

// ========= 2. Решение задачи ========= //
    probability_vec[0][0] = 1.0;
    probability_vec[1][0] = 1.0;
    for (size_t i = 2; i < n + 1; ++i)
        probability_vec[i][0] = 0.0;
    probability_vec[1][1] = 0.0;

    long double res = Calculate_probabilities(n, h, probability_vec);

// ========= 3. Вывод ответа ========= //
    std::cout << std::setprecision(10) << res << '\n';
}
