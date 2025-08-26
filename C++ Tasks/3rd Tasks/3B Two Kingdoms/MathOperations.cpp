#include "MathOperations.h"

// ========= Быстрое {(p_value^degree) mod prime_value}, используя метод бинарной экспоненты: O(log degree) ========= //
int64_t p_binFastExp(int64_t p_value, int degree, int64_t prime_value)
{
    int64_t res = 1;

    // 1. Пока степень degree больше 0
    while (degree)
    {
        // 1.1. Если последний бит степени равен 1 (то есть степень нечет): текущ p_value нужно учесть в рез-ат
        if (degree & 1)
        {
            // 1.1.1. Умножаем результат на p_value, берем по модулю (чтобы не было переполнения).
            res *= p_value;
            res %= prime_value;
        }

        // 1.2. Готовим p_value к следующему шагу: 
        // На каждой ит мы возводим p_value в квадрат — то есть, двигаемся по степеням: 1, 2, 4, 8, ...
        p_value = (p_value * p_value) % prime_value;

        // 1.3. Делим степень на 2 (переходим к след биту в разложении)
        degree >>= 1;
    }

    return res;
}

// ПРИМЕР:
// 5 = 101; 3^5 mod 7 ( p = 3, deg = 5)

// 0) res = 1 -> 
//      res *= 3 = 3
//      p = 3^2 = 9 % 7 = 2
//      deg = 2
// 1) Пропуск: бит = 0
// 2) Последний шаг -> 
//      res *= 4  = 12 % 7 = 5
// Ответ: 5
