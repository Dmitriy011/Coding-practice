#include "MemManager.h"

// ========= 1. �������� ������ (������� size) ========= //
int MemManager::AllocateMemory(int size)
{
    // 1. �� ������� ��������
    ++countOperations;
    // 2. ������ �� ����, ������������� ����� ���-�� ��������: ����� ��-�� ���������������� ��� chunks_list_.end()
    // ���� ��������� ������� - ���������� �� �������� ��������
    allocated_chunks.resize(countOperations, chunks_list.end());

    // 3. ���� ��� ��������� ������ ��� ������������ ���� ������ ������������
    if (memory_heap.Empty() || memory_heap.GetMax()->len < size)
        return -1;

    // 4. ��������� �� (������� �� ����) �� ����� ����� ������� �� �� ����
    // ��� ������ �������� ������ ����������� ���������� st
    std::list<Chunk>::iterator it_FreeChunk = memory_heap.ExtractMax();
    // 5. ������� ��� ������� �� ����� ��������� ������ (st � ��� ��� ����������� ����� = ��� ������� �������)
    Chunk newChunk(it_FreeChunk->st, size, false);
    // 6. ��������� ����� �� new_chunk � ������ ���� ������ ������ chunks_list_ ����� �� free_chunk (����� ���� �� ������� ��, �� �������� �������� ������)
    // + ����������: �� �� ������ ��� ����������� ���� new_chunk ��� ��������, ��������������� ������ �������
    allocated_chunks[countOperations - 1] = chunks_list.insert(it_FreeChunk, newChunk);

    // 7. ���� �� �������� ������� �� �������: ������� ��� �� ������, ������ ��� �� ��������� �����. 
    // ���������� ����� ������ ����������� �����.
    if (it_FreeChunk->len == size)
    {
        chunks_list.erase(it_FreeChunk);
        return allocated_chunks[countOperations - 1]->st;
    }

    // 8. ���� ���� ������, ��� ������: c������ ���� ������������ ������ (�� ��� �� �� size, ��� ��� �� �� size.)
    it_FreeChunk->len -= size;
    it_FreeChunk->st += size;
    // 9. ����� ���������� ��������� � ����������� ������� � memory_heap
    memory_heap.Insert(it_FreeChunk);

    // 10. ������� ������ ������ ���������� ������
    return allocated_chunks[countOperations - 1]->st;
}

// ========= 2. �������� ������ (������ num) ========= //
void MemManager::FreeMemory(int i_req)
{
    // 1. �� ������� ��������
    ++countOperations;

    // 2. ���� ������ num ��� ������, � allocated_chunks_[num - 1] ����� �������� �� �� ������� �� (�����: chunks_list.end()) 
    if (allocated_chunks[i_req - 1] == chunks_list.end())
        return;

    // 3. �������� ���� ��� ������� (�.�. ����������� ������) 
    allocated_chunks[i_req - 1]->isFree = true;

    // 4. ������ �������� �� �� ������� �������: ���� ������������� �� � �� 1�� � ������, � ���� ���� �������� ����, � ����� ���������� ����� ��
    if (allocated_chunks[i_req - 1] != chunks_list.begin())
    {
        auto it_prevChunk = std::prev(allocated_chunks[i_req - 1]);

        // 4.2. ���� �������� �� ��������: ������� � ����� ��
        if (it_prevChunk->isFree)
        {
            allocated_chunks[i_req - 1]->len += it_prevChunk->len;
            allocated_chunks[i_req - 1]->st = it_prevChunk->st;

            memory_heap.Remove(it_prevChunk->id);
            chunks_list.erase(it_prevChunk);
        }
    }

    // 5. ������ ������� �� �� ������� �������
    if (allocated_chunks[i_req - 1] != --(chunks_list.end()))
    {
        std::list<Chunk>::iterator next_chunk = std::next(allocated_chunks[i_req - 1]);

        // 5.1. ���� ���� �� ��������: ������� � ����� ��
        if (next_chunk->isFree)
        {
            allocated_chunks[i_req - 1]->len += next_chunk->len;

            memory_heap.Remove(next_chunk->id);
            chunks_list.erase(next_chunk);
        }
    }

    // 6. ��� ���������� �� � ����
    memory_heap.Insert(allocated_chunks[i_req - 1]);
}