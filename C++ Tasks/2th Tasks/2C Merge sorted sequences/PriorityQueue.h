#pragma once

// T � ��� ��������� (� ����� ������: std::pair<int, size_t>).
// Compare � ������� ��������� (��������, std::greater ��� min-heap).

// std::push_heap �� ������ ���� ������ ���������������.
// �� ������ ���, ����� ������ �������������� �������� ����(heap property), �� ���� :
// � ������ min - heap(std::greater) : elements[0] � ���������� �������.
// ��������� �������� ����������� �� ����������� �� ��������, � ���� ���, ����� ����� ���� ���������� ������� ������� �� O(log n)
template <typename T, class Compare>
class PriorityQueue
{
public:
    // ���������� ���������� ������� (������ �������� � elements.front())
    const T& top() const { return elements.front(); }

    void push(const T& obj)
    {
        elements.emplace_back(std::move(obj));                          // 1) ��������� ������� � ����� �������
        std::push_heap(elements.begin(), elements.end(), orderCompare); // 2) ������������� ������ ���, ����� �� ���� ����� �� ������� orderCompare
    }                                                                   // "���������� �����" ��������� �������, ����� ������������ ���������� �������.

    // ������� ���������� �������:
    void pop()
    {
        std::pop_heap(elements.begin(), elements.end(), orderCompare);  // 1) ���������� ��� � �����,
        elements.pop_back();                                            // 2) �������.
    }

    // ���� �� ���������.
    bool isEmpty() const { return elements.empty(); }

private:
    std::vector<T> elements{};      // ���������� ������ (���������� ����).
    Compare orderCompare{};         // ������ ��������� (��������, std::greater).
};
