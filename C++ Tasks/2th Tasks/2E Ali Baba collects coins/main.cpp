#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

// n - количество монет

struct Coin
{
    int32_t pos;   // Положение монеты
    int32_t time;  // Дедлайн в сек (время, до которого монету надо собрать)

    // Сортировка монет сначала по коорд, затем по дедлайну (если коорд совпадают).
    bool operator<(Coin rhs) const
    {
        return std::make_pair(pos, time) < std::make_pair(rhs.pos, rhs.time);
    }

    // Сложение 2уъ монет как векторов (используется в DP, где pos и time будут накапливаться как путь и время движ)
    Coin operator+(Coin rhs) const
    {
        return { pos + rhs.pos, time + rhs.time };
    }
};

int main()
{
    const int32_t inf = 1e6;

// -- Считывание задачи --//
    size_t n;
    std::cin >> n;
    std::vector<Coin> coins(n);

    for (size_t i_coin = 0; i_coin < n; ++i_coin)
        std::cin >> coins[i_coin].pos >> coins[i_coin].time;

// -- Решение задачи --// 
    std::sort(coins.begin(), coins.end());                                                  // Сортирует монеты по позиции (и времени, если позиции совпадают)
    std::vector<std::vector<Coin>> dp(n, std::vector<Coin>(n));                             // Хранит минимальные накопленные значения pos и time при сборе всех монет от i до j
    for (size_t h_step = 1; h_step < n; ++h_step)
    {
        for (size_t index = 0; index < n - h_step; ++index)
        {
            dp[index][index + h_step] = { inf, inf };                                           // Перебирает все подпоследовательности [index, index + h_step], дл от 2 до n, инициализируя их как «невозможные»

            int32_t tmp1_coordCoin = std::abs(std::next(coins.begin(), index)->pos -            // Вариант 1) идём от правой части к левой
                std::next(coins.begin(), index + 1)->pos);
            int32_t tmp1_time = std::abs(std::next(coins.begin(), index)->pos -
                std::next(coins.begin(), index + h_step)->pos);
            Coin tmp1_coin = { tmp1_coordCoin, tmp1_time };                                     // tmp1_coin — сколько нужно пройти и сколько времени пройдёт, если идти от позиции index влево.
            Coin distances = dp[index + 1][index + h_step] + tmp1_coin;                         // Складываем с уже посчитанным путём dp[index + 1][index + h_step].

            if (distances.pos <= coins[index].time || distances.time <= coins[index].time)      // Если мы успеваем к монете index — обновляем dp.
                dp[index][index + h_step].pos = std::min(distances.pos, distances.time);

            int32_t tmp2_coordCoin = std::abs(std::next(coins.begin(), index)->pos -                    // Вариант 2) идём от левой части к правой
                std::next(coins.begin(), index + h_step)->pos);
            int32_t tmp2_time = std::abs(std::next(coins.begin(), index + h_step - 1)->pos -
                std::next(coins.begin(), index + h_step)->pos);
            Coin tmp2_coin = { tmp2_coordCoin, tmp2_time };
            Coin times = dp[index][index + h_step - 1] + tmp2_coin;

            if (times.pos <= coins[index + h_step].time || times.time <= coins[index + h_step].time)    // Проверяем, успеваем ли к coins[index + h_step].
                dp[index][index + h_step].time = std::min(times.pos, times.time);
        }
    }
    int32_t ans = std::min(dp.front().back().pos, dp.front().back().time);                     // Из dp[0][n - 1] берётся лучший результат, где мы собрали все монеты (независимо, с какой стороны начали)


// -- Вывод решения --// 
    if (ans == inf)
        std::cout << "No solution";
    else
        std::cout << ans;

    std::cout << '\n';

    return 0;
}
