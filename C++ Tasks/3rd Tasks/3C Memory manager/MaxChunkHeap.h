#pragma once

#include <iostream>
#include <vector>
#include <list>

#include "Chunk.h"


// ========= 1. Реализация max-кучи (хранит ит на эл-ты списка std::list<Chunk>) ========= //
// Используется для поиска самого большого свободн бл памяти.
class MaxChunkHeap
{
public:
    bool Empty() const { return arr.empty(); }

    // Просеивание вниз
    void Heapify(int root_index);

    void Insert(std::list<Chunk>::iterator new_key);

    // Всегда в arr[0]
    std::list<Chunk>::iterator GetMax() { return arr[0]; }         

    std::list<Chunk>::iterator ExtractMax();

    void Remove(int id);

    MaxChunkHeap() {}

private:
    void ChangeID(int id, std::list<Chunk>::iterator new_key);

    // Вектор, в котором кажд эл — это итератор на узел списка chunks_list.
    std::vector<std::list<Chunk>::iterator> arr;

};
