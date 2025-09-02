#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

#include "Coin.h"


//* n - количество монет

int main()
{
    const int32_t inf = 1e6;

// ========= 1. Считывание задачи ========= // 
    size_t n;
    std::cin >> n;
    std::vector<Coin> coins(n);

    for (size_t i_coin = 0; i_coin < n; ++i_coin)
        std::cin >> coins[i_coin].pos >> coins[i_coin].time;

// ========= 2. Решение задачи ========= // 

//**** 1) Сортирует монеты по позиции (и времени, если позиции совпадают)

//* DP: Хранит минимальные накопленные значения pos и time при сборе всех монет от i до j

//**** 2) Перебирает все подпоследовательности [index, index + h_step], дл от 2 до n, инициализируя их как «невозможные»
//**** 3) Вариант 1 идём от правой части к левой

//* tmp1_coin - сколько нужно пройти и сколько времени пройдёт, если идти от позиции index влево.

//**** 4) Складываем с уже посчитанным путём dp[index + 1][index + h_step].
//**** 5) Если мы успеваем к монете index — обновляем dp.
//**** 6) Вариант 2 идём от левой части к правой
//**** 7) Проверяем, успеваем ли к coins[index + h_step]
//**** 8) Из dp[0][n - 1] берётся лучший результат, где мы собрали все монеты (независимо, с какой стороны начали)

    std::sort(coins.begin(), coins.end());                                                  
    std::vector<std::vector<Coin>> DP(n, std::vector<Coin>(n));                             
    for (size_t h_step = 1; h_step < n; ++h_step)
    {
    // 2) 
        for (size_t index = 0; index < n - h_step; ++index)
        {
            DP[index][index + h_step] = { inf, inf };                                           

    // 3) 
            int32_t tmp1_coordCoin = std::abs(std::next(coins.begin(), index)->pos - std::next(coins.begin(), index + 1)->pos);
            int32_t tmp1_time = std::abs(std::next(coins.begin(), index)->pos - std::next(coins.begin(), index + h_step)->pos);
            Coin tmp1_coin = { tmp1_coordCoin, tmp1_time };                            
    // 4) 
            Coin distances = DP[index + 1][index + h_step] + tmp1_coin;                        

    // 5) 
            if (distances.pos <= coins[index].time || distances.time <= coins[index].time)
                DP[index][index + h_step].pos = std::min(distances.pos, distances.time);

    // 6) 
            int32_t tmp2_coordCoin = std::abs(std::next(coins.begin(), index)->pos - std::next(coins.begin(), index + h_step)->pos);
            int32_t tmp2_time = std::abs(std::next(coins.begin(), index + h_step - 1)->pos - std::next(coins.begin(), index + h_step)->pos);
            Coin tmp2_coin = { tmp2_coordCoin, tmp2_time };
            Coin times = DP[index][index + h_step - 1] + tmp2_coin;

    // 7) 
            if (times.pos <= coins[index + h_step].time || times.time <= coins[index + h_step].time)
                DP[index][index + h_step].time = std::min(times.pos, times.time);
        }
    }
    // 8) 
    int32_t ans = std::min(DP.front().back().pos, DP.front().back().time);


// ========= 3. Вывод решения ========= // 
    if (ans == inf)
        std::cout << "No solution";
    else
        std::cout << ans;

    std::cout << '\n';

    return 0;
}
