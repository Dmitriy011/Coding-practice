#pragma once

//* T — тип элементов (в нашем случае: std::pair<int, size_t>).
//* Compare — функция сравнения (например, std::greater для min-heap).

//* std::push_heap НЕ делает весь вектор отсортированным.
//* Он делает так, чтобы вектор соответствовал свойству кучи(heap property), то есть :
//* В случае min - heap(std::greater) : elements[0] — наименьший элемент.
//* Остальные элементы расположены не обязательно по убыванию, а лишь так, чтобы можно было эффективно извлечь минимум за O(log n)
template <typename T, class Compare>
class PriorityQueue
{
public:
    //* Возвращает наименьший элемент (всегда хрнатися в elements.front())
    const T& top() const { return elements.front(); }

    void push(const T& obj)
    {
//**** 1)  Добавляем элемент в конец вектора
//**** 2) Перестраиваем вектор так, чтобы он стал кучей по правилу orderCompare - "Просеивает вверх" последний элемент, чтобы восстановить правильный порядок.

        elements.emplace_back(std::move(obj));                         
        std::push_heap(elements.begin(), elements.end(), orderCompare);  
    }                                                                   

    //* Удаляет наименьший элемент:
    void pop()
    {
//**** 1) Перемещает его в конец,
//**** 2) Удаляет

        std::pop_heap(elements.begin(), elements.end(), orderCompare);
        elements.pop_back();                                          
    }

    //* Пуст ли контейнер.
    bool isEmpty() const { return elements.empty(); }

private:

//* elements - Внутренний вектор (реализация кучи).
//* orderCompare - Объект сравнения (например, std::greater).

    std::vector<T> elements{};      
    Compare orderCompare{};        
};
