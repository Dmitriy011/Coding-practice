#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <functional>

// n- количество массивов
// m - длиан последовательности

//Ограничения:
// 1)Время: O(mn log n) — типичная сложность для k - way merge с использованием кучи.
// 2) Память: O(mn) — можно хранить все элементы (это и есть входные данные), но работать эффективно.

// T — тип элементов (в нашем случае: std::pair<int, size_t>).
// Compare — функция сравнения (например, std::greater для min-heap).

// std::push_heap НЕ делает весь вектор отсортированным.
// Он делает так, чтобы вектор соответствовал свойству кучи(heap property), то есть :
// В случае min - heap(std::greater) : elements[0] — наименьший элемент.
// Остальные элементы расположены не обязательно по убыванию, а лишь так, чтобы можно было эффективно извлечь минимум за O(log n)
template <typename T, class Compare>
class PriorityQueue
{
public:
    // Возвращает наименьший элемент (всегда хрнатися в elements.front())
    const T& top() const { return elements.front(); }

    void push(const T& obj)
    {
        elements.emplace_back(std::move(obj));                          // 1) Добавляем элемент в конец вектора
        std::push_heap(elements.begin(), elements.end(), orderCompare); // 2) Перестраиваем вектор так, чтобы он стал кучей по правилу orderCompare
    }                                                                   // "Просеивает вверх" последний элемент, чтобы восстановить правильный порядок.

    // Удаляет наименьший элемент:
    void pop()
    {
        std::pop_heap(elements.begin(), elements.end(), orderCompare);  // 1) перемещает его в конец,
        elements.pop_back();                                            // 2) удаляет.
    }

    // Пуст ли контейнер.
    bool isEmpty() const { return elements.empty(); }

private:
    std::vector<T> elements{};      // Внутренний вектор (реализация кучи).
    Compare orderCompare{};         // Объект сравнения (например, std::greater).
};

// Проверяет, остались ли ещё элементы в данной последовательности: true, если есть что читать.
bool isProcessedCurArr(const size_t countProcessed_inArray, const size_t m_sizeArr)
{
    return countProcessed_inArray < m_sizeArr;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

// -- Считывание задачи --// 
    size_t n;
    size_t m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> arrs(n, std::vector<int>(m));                  // Двумерный вектор: n строк по m элементов.
    for (size_t i_arr = 0; i_arr < n; ++i_arr)
    {
        for (size_t j_el = 0; j_el < m; ++j_el)
            std::cin >> arrs[i_arr][j_el];
    }

// -- Решение задачи --// 

    std::vector<size_t> countProcessed(n, 0);                                   // Вектор счётчиков: сколько эл-ов уже обработано в каждой строке.

    // Создаём min-heap. В ней храним пары {знач, номер массива}.
    PriorityQueue<std::pair<int, size_t>, std::greater<std::pair<int, size_t>>> heap;
    // Кладём 1ые эл-ты всех n массивов в кучу.
    for (size_t i_arr = 0; i_arr < n; ++i_arr)
    {
        std::pair<int, size_t> val = std::make_pair(arrs[i_arr][countProcessed[i_arr]], i_arr);
        heap.push(val);
    }

    while (!heap.isEmpty())                                                    // Пока куча не пуста — продолж извлеч миним эл-ов.
    {
        std::cout << heap.top().first << ' ';                                  // Выводим наим знач из кучи (всегда на heap.top()).

        size_t i_curArr = heap.top().second;                                   // Получаем номер массива, из котор был эл.
        heap.pop();
        ++countProcessed[i_curArr];                                            // Ув счётчик обработанных эл-ов в этом массиве.

        bool isProcessed = isProcessedCurArr(countProcessed[i_curArr], m);     // Если в том массиве ещё остались эл-ты — кладём след эл в кучу.
        if (isProcessed)
        {
            std::pair<int, size_t> val = std::make_pair(arrs[i_curArr][countProcessed[i_curArr]], i_curArr);
            heap.push(val);
        }
    }

    std::cout << '\n';

    return 0;
}
