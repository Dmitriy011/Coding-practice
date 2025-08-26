#include <iostream>
#include <vector>
#include <stdexcept>
#include <cstring>

// NOLINT (Важно, чтобы FixedSet не использовал rand(): только std::mt19937)
// «Перехватывает» вызов стандартного rand() и вызывает исключение
int rand()
{  
    throw std::runtime_error("Don't use rand");
}

#include "Fixed_set.h"

// -- Считывание условия задачи --//
std::vector<int> ReadSequence() 
{
    size_t n;
    std::cin >> n;

    std::vector<int> sequence(n);
    for (auto& current : sequence)
        std::cin >> current;

    return sequence;
}

// По каждому request проверяет: есть ли он в FixedSet. Возвращает вектор bool.
std::vector<bool> PerformRequests(const std::vector<int>& requests, const FixedSet& set) 
{
    std::vector<bool> request_answers;
    request_answers.reserve(requests.size());
    for (int request : requests) 
        request_answers.push_back(set.Contains(request));

    return request_answers;
}

// Печатает: "Yes" — если true; "No" — если false
void PrintRequestsResponse(const std::vector<bool>& request_answers)
{
    for (bool answer : request_answers) 
        std::cout << (answer ? "Yes" : "No") << "\n";
}

// ========= TESTING ZONE ========= //

// 1) Выводит ош, если зн-я expected и actual (юнит-тест)
#define ASSERT_EQ(expected, actual) do { \
    auto __expected = expected; \
    auto __actual = actual; \
    if (!(__expected == __actual)) { \
        std::cerr << __FILE__ << ":" << __LINE__ << ": Assertion error" << std::endl; \
        std::cerr << "\texpected: " << __expected << " (= " << #expected << ")" << std::endl; \
        std::cerr << "\tgot: " << __actual << " (= " << #actual << ")" << std::endl; \
        std::cerr << "=========== FAIL ===========\n"; \
        throw std::runtime_error("Check failed"); \
    } \
} while (false)

// Проверяет, что пустое множество не содержит 0.
void Empty()
{
    FixedSet set;
    set.Initialize({});
    ASSERT_EQ(false, set.Contains(0));
}

// Проверка корр вставленных и не вставленных знач.
void Simple()
{
    FixedSet set;
    set.Initialize({ -3, 5, 0, 3, 7, 1 });

    ASSERT_EQ(true, set.Contains(0));
    ASSERT_EQ(true, set.Contains(-3));
    ASSERT_EQ(true, set.Contains(1));
    ASSERT_EQ(false, set.Contains(2));
    ASSERT_EQ(false, set.Contains(4));
}

// Тестирует повторн инициализацию FixedSet с разными вх. Каждый раз убеждаемся, что: новые эл-ты находятся, старые уже не находятся.
void RepeatInitialize()
{
    FixedSet set;
    const int shift = 100;     // Сдвиг, чтобы нов эл-ты не пересекались со старыми.
    int element = 0;           // Текущ эл-т, с которого начинается генерация нового набора чисел.
    int last = -1;             // Последний эл-т из предыдущ инициализации, чтобы проверить, что он больше не содержится в set

    // Цикл: 10 раз создаём и инициализируем FixedSet с различными по дл и содержимому массивами.
    for (int elements_count = 0; elements_count < 10; ++elements_count)
    {
        // Создаём вектор elements из elements_count чисел: element, element + 1, ...
        std::vector<int> elements;
        for (int i = 0; i < elements_count; ++i)
            elements.push_back(element++);

        // Переинициализируем FixedSet 
        set.Initialize(elements);

        // Проверка: все эл-ты из elements должны находиться в set.
        for (auto elem : elements)
            ASSERT_EQ(true, set.Contains(elem));

        // Последний эл-т предыдущ инициализации больше не должен содержаться в мн-ве.
        ASSERT_EQ(false, set.Contains(last));
        last = element - 1;
        element += shift;
    }
}

// Создаются две близкие т., которые могут попасть в одну корзину.
void Magic()
{
#ifdef MAGIC
    std::cerr << "You've been visited by Hash Police!\n";
    std::cerr << "Probably your hash table is not as good as you think.\n";
    std::cerr << "No ticket today, but you better be careful.\n\n";
    int first = -1'000'000'000;
    int second = first + MAGIC;
    FixedSet set;
    set.Initialize({ first, second });
    ASSERT_EQ(true, set.Contains(first));
    ASSERT_EQ(true, set.Contains(second));
    ASSERT_EQ(false, set.Contains(0));
#endif
}

// ========= MAIN ========= //

int main(int argc, char** argv) 
{
    // Если программа запущена с аргументом --testing, то: выполняются тесты → RunTests()
    if (argc > 1 && !strcmp(argv[1], "--testing"))
    {
        std::cerr << "Running tests...\n";

       Empty();
       Simple();
       RepeatInitialize();
       Magic();

        std::cerr << "Tests are passed!\n";

        return 0;
    }

    std::ios::sync_with_stdio(false);

    auto numbers = ReadSequence();
    auto requests = ReadSequence();
    FixedSet set;
    set.Initialize(numbers);
    PrintRequestsResponse(PerformRequests(requests, set));

    return 0;
}


