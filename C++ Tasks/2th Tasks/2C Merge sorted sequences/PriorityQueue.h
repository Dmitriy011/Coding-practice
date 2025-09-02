#pragma once

//* T � ��� ��������� (� ����� ������: std::pair<int, size_t>).
//* Compare � ������� ��������� (��������, std::greater ��� min-heap).

//* std::push_heap �� ������ ���� ������ ���������������.
//* �� ������ ���, ����� ������ �������������� �������� ����(heap property), �� ���� :
//* � ������ min - heap(std::greater) : elements[0] � ���������� �������.
//* ��������� �������� ����������� �� ����������� �� ��������, � ���� ���, ����� ����� ���� ���������� ������� ������� �� O(log n)
template <typename T, class Compare>
class PriorityQueue
{
public:
    //* ���������� ���������� ������� (������ �������� � elements.front())
    const T& top() const { return elements.front(); }

    void push(const T& obj)
    {
//**** 1)  ��������� ������� � ����� �������
//**** 2) ������������� ������ ���, ����� �� ���� ����� �� ������� orderCompare - "���������� �����" ��������� �������, ����� ������������ ���������� �������.

        elements.emplace_back(std::move(obj));                         
        std::push_heap(elements.begin(), elements.end(), orderCompare);  
    }                                                                   

    //* ������� ���������� �������:
    void pop()
    {
//**** 1) ���������� ��� � �����,
//**** 2) �������

        std::pop_heap(elements.begin(), elements.end(), orderCompare);
        elements.pop_back();                                          
    }

    //* ���� �� ���������.
    bool isEmpty() const { return elements.empty(); }

private:

//* elements - ���������� ������ (���������� ����).
//* orderCompare - ������ ��������� (��������, std::greater).

    std::vector<T> elements{};      
    Compare orderCompare{};        
};
