#pragma once

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
