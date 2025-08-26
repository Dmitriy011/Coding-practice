#pragma once

#include <iostream>
#include <list>

#include "MaxChunkHeap.h"

class MemManager
{
public:
    explicit MemManager(int sizeMem)
    {
        chunks_list.push_back(Chunk(1, sizeMem, true, 0));
        memory_heap.Insert(chunks_list.begin());
        countOperations = 0;
    }

    int AllocateMemory(int size);

    void FreeMemory(int num);

private:
    MaxChunkHeap memory_heap;
    std::list<Chunk> chunks_list;                                    
    std::vector<std::list<Chunk>::iterator> allocated_chunks;       // Хранит итераторы на выделенные блоки по номеру запроса
    int countOperations;                                            // Cчетчик общ кол-ва операций (выделения и освобождения), который используется для: 
                                                                         // 1) Учета номера текущ запроса 
                                                                         // 2) Связи между запросами и выделенными блоками: Вектор allocated_chunks_ хранит итераторы на выделенные блоки, и его индекс соответствует номеру запроса T.
};

// 1) chunks_list
// * Двусвязный список всех блоков памяти (свободных и занятых)
// * [ Chunk A ] <-> [ Chunk B ] <-> [ Chunk C ] <-> [ Chunk D ]
// * У каждого блока есть поля : size — размер блока; free — свободен он или занят; id — номер в куче (если блок свободный)

// 2) memory_heap: куча для быстрого поиска макс свободн бл
// * Массив указателей на свободные блоки из списка
// * arr (куча): 0 → Chunk C(size = 80, id = 0) 
//             1 → Chunk A(size = 50, id = 1)
//             ...

// list<Chunk>:                    MaxChunkHeap:
// Chunk A (id = 1)   ←----------→ arr[1] = &Chunk A
// Chunk B (id = 3)   ←----------→ arr[3] = &Chunk B

// !!! Каждый Chunk в списке памяти знает, где он находится в куче (id).

