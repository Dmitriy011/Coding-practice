#include "MemManager.h"

// ========= 1. Выделить память (размера size) ========= //
int MemManager::AllocateMemory(int size)
{
    // 1. Ув счетчик операций
    ++countOperations;
    // 2. Должен им разм, соответствующ текущ кол-ву операций: новые эл-ты инициализируются как chunks_list_.end()
    // Если выделение успешно - заменяется на валидный итератор
    allocated_chunks.resize(countOperations, chunks_list.end());

    // 3. Если нет свободных блоков ИЛИ максимальный блок меньше запрошенного
    if (memory_heap.Empty() || memory_heap.GetMax()->len < size)
        return -1;

    // 4. Извлекаем ит (удаляем из кучи) на самый больш свободн бл из кучи
    // При равных размерах должна учитываться наименьшая st
    std::list<Chunk>::iterator it_FreeChunk = memory_heap.ExtractMax();
    // 5. Создаем нов занятый бл перед свободным блоком (st — поз нач выделенного блока = нач старого свободн)
    Chunk newChunk(it_FreeChunk->st, size, false);
    // 6. Вставляем новый бл new_chunk в список всех блоков памяти chunks_list_ перед ит free_chunk (котор указ на свободн бл, из которого выделяем память)
    // + Возвращает: Ит на только что вставленный блок new_chunk под индексом, соответствующим номеру запроса
    allocated_chunks[countOperations - 1] = chunks_list.insert(it_FreeChunk, newChunk);

    // 7. Если бл идеально подошел по размеру: удаляем его из списка, потому что он полностью занят. 
    // Возвращаем адрес начала выделенного блока.
    if (it_FreeChunk->len == size)
    {
        chunks_list.erase(it_FreeChunk);
        return allocated_chunks[countOperations - 1]->st;
    }

    // 8. Если блок больше, чем запрос: cвободн блок «сдвигается» вправо (ум его дл на size, нач поз ув на size.)
    it_FreeChunk->len -= size;
    it_FreeChunk->st += size;
    // 9. Снова становится свободным и вставляется обратно в memory_heap
    memory_heap.Insert(it_FreeChunk);

    // 10. Возврат адреса начала выделенной памяти
    return allocated_chunks[countOperations - 1]->st;
}

// ========= 2. Очистить память (запрос num) ========= //
void MemManager::FreeMemory(int i_req)
{
    // 1. Ув счетчик операций
    ++countOperations;

    // 2. Если запрос num был успешн, в allocated_chunks_[num - 1] лежит валидный ит на выделен бл (иначе: chunks_list.end()) 
    if (allocated_chunks[i_req - 1] == chunks_list.end())
        return;

    // 3. Помечаем блок как свободн (т.к. освобождаем память) 
    allocated_chunks[i_req - 1]->isFree = true;

    // 4. Провер предыдущ бл на возможн слияния: если освобождаемый бл — не 1ый в списке, у него есть предыдущ блок, и можем попытаться объед их
    if (allocated_chunks[i_req - 1] != chunks_list.begin())
    {
        auto it_prevChunk = std::prev(allocated_chunks[i_req - 1]);

        // 4.2. Если предыдущ бл свободен: сливаем с текущ бл
        if (it_prevChunk->isFree)
        {
            allocated_chunks[i_req - 1]->len += it_prevChunk->len;
            allocated_chunks[i_req - 1]->st = it_prevChunk->st;

            memory_heap.Remove(it_prevChunk->id);
            chunks_list.erase(it_prevChunk);
        }
    }

    // 5. Провер следующ бл на возможн слияния
    if (allocated_chunks[i_req - 1] != --(chunks_list.end()))
    {
        std::list<Chunk>::iterator next_chunk = std::next(allocated_chunks[i_req - 1]);

        // 5.1. Если след бл свободен: сливаем с текущ бл
        if (next_chunk->isFree)
        {
            allocated_chunks[i_req - 1]->len += next_chunk->len;

            memory_heap.Remove(next_chunk->id);
            chunks_list.erase(next_chunk);
        }
    }

    // 6. Доб освобожден бл в кучу
    memory_heap.Insert(allocated_chunks[i_req - 1]);
}