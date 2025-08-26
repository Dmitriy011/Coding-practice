#pragma once

#include <iostream>
#include <vector>
#include <list>

#include "Chunk.h"


// ========= 1. ���������� max-���� (������ �� �� ��-�� ������ std::list<Chunk>) ========= //
// ������������ ��� ������ ������ �������� ������� �� ������.
class MaxChunkHeap
{
public:
    bool Empty() const { return arr.empty(); }

    // ����������� ����
    void Heapify(int root_index);

    void Insert(std::list<Chunk>::iterator new_key);

    // ������ � arr[0]
    std::list<Chunk>::iterator GetMax() { return arr[0]; }         

    std::list<Chunk>::iterator ExtractMax();

    void Remove(int id);

    MaxChunkHeap() {}

private:
    void ChangeID(int id, std::list<Chunk>::iterator new_key);

    // ������, � ������� ���� �� � ��� �������� �� ���� ������ chunks_list.
    std::vector<std::list<Chunk>::iterator> arr;

};
