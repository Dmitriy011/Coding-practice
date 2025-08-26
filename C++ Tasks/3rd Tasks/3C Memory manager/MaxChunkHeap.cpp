#include <iostream>
#include <vector>
#include <list>

#include "MaxChunkHeap.h" 
#include "Chunk.h" 


// Просеивание вниз, начиная с вершины index_root: Родитель всегда больше или равен детям.
void MaxChunkHeap::Heapify(int index_root)
{
    // Изначально считаем корень наибольшим
    int L_son_index = 2 * index_root + 1;
    int R_son_index = 2 * index_root + 2;
    int largest_index = index_root;

    // Проверяем, сущ ли потомок и сравниваем родителя и детей, выбирает наибольший -> largest_index хранит индекс наибольшего из 3ех
    if (L_son_index < static_cast<int>(arr.size()) && *(arr[L_son_index]) > *(arr[largest_index]))
        largest_index = L_son_index;

    if (R_son_index < static_cast<int>(arr.size()) && *(arr[R_son_index]) > *(arr[largest_index]))
        largest_index = R_son_index;

    // Если наибольший эл — не текущий корень, делаем обмен:
    if (largest_index != index_root)
    {
        std::swap(arr[index_root]->id, arr[largest_index]->id);
        std::swap(arr[index_root], arr[largest_index]);

        Heapify(largest_index);
    }
}

void MaxChunkHeap::Insert(std::list<Chunk>::iterator new_it)
{
    // Вставили новый эл в самый низ;
    arr.push_back(new_it);

    // Возможно нужно поднять
    ChangeID(static_cast<int>(arr.size()) - 1, new_it);

    // arr[n - 1] = new_it
    // new Chank A id = (n - 1)
}

std::list<Chunk>::iterator MaxChunkHeap::ExtractMax()
{
    std::list<Chunk>::iterator max_el = arr[0];

    arr[0] = arr[static_cast<int>(arr.size()) - 1];
    arr[0]->id = 0;
    arr.pop_back();
    Heapify(0);

    return max_el;
}

void MaxChunkHeap::Remove(int id_chunk)
{
    if (arr.empty())
        return;

    arr[id_chunk] = arr[arr.size() - 1];
    arr[id_chunk]->id = id_chunk;
    arr.pop_back();

    ChangeID(id_chunk, arr[id_chunk]);
}

void MaxChunkHeap::ChangeID(int changed_ID, std::list<Chunk>::iterator new_it)
{
    arr[changed_ID] = new_it;
    new_it->id = changed_ID;

    Heapify(changed_ID);

    // Если родитель меньше, чем текущий элемент — меняем их местами
    while (changed_ID > 0 && *(arr[(changed_ID - 1) / 2]) < *(arr[changed_ID]))
    {
        std::swap(arr[(changed_ID - 1) / 2]->id, arr[changed_ID]->id);
        std::swap(arr[(changed_ID - 1) / 2], arr[changed_ID]);

        // Поднимаемся наверх
        changed_ID = (changed_ID - 1) / 2;
    }
}

