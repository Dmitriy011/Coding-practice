#include <vector>
#include <random>
#include <stdexcept>

// Нужен, чтобы все ключи были положительными 
constexpr int kKeyMaxVal = 1e9;
//Используется как модуль в хеш-функции, чтобы избежать коллизий ( Большое простое число. )
constexpr int kMaxPrime = 2000000011;

// -- Хэш функция -- //
class HashFuncClass
{
public:
    void Initialize(int a, int b)
    {
        this->a = a;
        this->b = b;
    }

    // Хеш-функция вида a * x + b (mod P)
    size_t Hash(int key_val, size_t mod) const { return ((static_cast<int64_t>(a) * key_val + b) % kMaxPrime) % mod; }

private:
    int a;
    int b;
};

// Неизменяемое мн-во целых чисел с быстрыми запросами на принадлежность.
// Память — O(n).
class FixedSet
{
public:
    FixedSet();

    // Должен за O(n) в среднем.
    void Initialize(const std::vector<int>& arr);

    // Должен за O(1) в худшем случае: используется двухуровневое хэширование
    bool Contains(int value_search) const;

private:
    // Основное хранилище зн-ий: каждая ячейка table[i] — это отдельная 2ая хеш-таблица для корзины i.
    // Сначала 1ая хеш-функция (hash1_func_) определяет номер корзины i = h1(key)
    // Потом из table[i] достаём нужную яч j = h2(key) и проверяем, лежит ли там нужное число.
    // Размер 2ой таблицы равен n_i^2 (где n_i — число эл-ов в корзине i).
    std::vector<std::vector<int>> table;

    // Объект класса, реализующий 1ую хеш-функцию h1.
    // Распределяет все эл-ты по корзинам: int bucket = hash1_func_.Hash(key, table.size());
    HashFuncClass hash1_func;

    // Вектор объектов, где hash2_func_[i] — это 2ая хеш-функция для корзины i.
    // Для каждой корзины мы подбираем свою 2ую хеш-функцию так, чтобы не было коллизий в пределах этой корзины: int pos = hash2_func_[i].Hash(key, table[i].size());
    std::vector<HashFuncClass> hash2_func_;

    // Генератор случ чисел 
    std::mt19937 gen_;
    std::uniform_int_distribution<int64_t> a_generated_;
    std::uniform_int_distribution<int64_t> b_generated_;
};

inline FixedSet::FixedSet()
{
    // Настраиваются гр генерации случ чисел a и b для хеш-функций.
    a_generated_.reset();
    b_generated_.reset();

    // a != 0, иначе хеш-функция станет постоянной.
    a_generated_.param(std::uniform_int_distribution<int64_t>::param_type (1, kMaxPrime - 1));
    b_generated_.param(std::uniform_int_distribution<int64_t>::param_type (0, kMaxPrime - 1));
}

inline void FixedSet::Initialize(const std::vector<int>& arr)
{
    // Размер хэш-таблицы
    size_t size_table = arr.size();

    // Таблицу делим на size_table корзин: у каждой корзины будет своя вторая таблица.
    table.resize(size_table);

    hash2_func_.resize(size_table);

    if (size_table == 0)
        return;

    std::vector<std::vector<size_t>> key_table_matr(size_table);
    size_t size_mem = 0;

// -- Выбор хорошей хеш-функции 1го уровня -- // 
// 
// Цель: добиться, чтобы ∑nᵢ² ≤ 10n, то есть в ср по корзине nᵢ² ≈ 10n / n = 10.
// Вероятность найти хор ф-ию h1 с такими св-ми — достаточно высокая, поэтому ожидание числа попыток — Const.
    do
    {
        // 1. Случ образом выбираем a, b — параметры первой хеш-функции
        hash1_func.Initialize(a_generated_(gen_), b_generated_(gen_));

        // 2. Распределение ключей по корзинам
        for (size_t i = 0; i < arr.size(); ++i)
        {
            int tmp_val = arr[i];               // Оригинальное значение.    
            int tmp_key = kKeyMaxVal + tmp_val; // Искусственно сдвинутое на +1e9 значение, чтобы все ключи были положительными.

            // hash1_func_.Hash(...) определяет в какую корзину положить ключ.
            // В key_table_matr[i] собираются все ключи, попавшие в i-ю корзину
            key_table_matr[hash1_func.Hash(tmp_key, size_table)].push_back(tmp_key);
        }

        // 3. ценка “качества” распределения
        size_mem = 0;
        for (size_t i = 0; i < key_table_matr.size(); ++i)
        {
            // Для каждой корзины i считаем n_i * n_i
            std::vector<size_t> n_i = key_table_matr[i];

            // Сумма квадратов n_i — это память, которую придётся выделить для 2го уровня.
            size_mem = size_mem + n_i.size() * n_i.size();
        }
    } while (size_mem > 10 * size_table);

// -- Построение 2го уровня -- // 
    size_t index_bucket = 0;
    while (index_bucket < size_table)
    {
        // 1. Для каждой корзины подбирается хеш-функция 2го уровня hash2_func_[i], которая должна разместить все ключи без коллизий в nᵢ² слотах.
        hash2_func_[index_bucket].Initialize(a_generated_(gen_), b_generated_(gen_));
        table[index_bucket] = std::vector<int>(key_table_matr[index_bucket].size() * key_table_matr[index_bucket].size(), -1);

        // 2. Проверка на коллизии (Подбираем хеш-функцию, пока не будет ни одной коллизии)
        bool isnt_collision = true;
        for (size_t i_it = 0; i_it < key_table_matr[index_bucket].size(); ++i_it)
        {
            size_t key = key_table_matr[index_bucket][i_it];
            size_t index_in_bucket = hash2_func_[index_bucket].Hash(key, table[index_bucket].size());


            if (table[index_bucket][index_in_bucket] != -1)
            {
                isnt_collision = false;
                break;
            }

            table[index_bucket][index_in_bucket] = key;
        }

        if (isnt_collision == true)
            ++index_bucket;
    }
}

bool FixedSet::Contains(int value_search) const
{
    // Если таблица пуста 
    if (table.empty())
        return false;

    // Вычисляем key, чтобы был положительным значенмем 
    int key = kKeyMaxVal + value_search;
    // Хешируем 1ой функцией → получаем индекс корзины.
    size_t index_bucket = hash1_func.Hash(key, table.size());

    // Если корзина пустая
    if (table[index_bucket].empty())
        return false;
    else
    {
        // Хешируем 2ой функцией для этой корзины.
        size_t index_in_bucket = hash2_func_[index_bucket].Hash(key, table[index_bucket].size());

        return (table[index_bucket][index_in_bucket] == key);
    }

    return false;
}
