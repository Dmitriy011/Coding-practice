#include <iostream>
#include <cstdio>
#include <vector>
#include <list>
#include <algorithm>

#include "Chunk.h"
#include "MaxChunkHeap.h" 
#include "MemManager.h" 

// Массив из N последовательных яч памяти, пронумерованных от 1 дл N
// Задача: обрабатывать запросы приложений на выделение и освобождение памяти

// 1) Запрос на выделение памяти имеет параметр: K - выделить K последовательных ячеек 
// 2) Менеджер выделяет память из самого длин свободн блока, а если неск, то выбирает, у которого номер 1ой яч — наим.

// 1) Запрос на освобождение памяти имеет параметр: T - освободить память, выделенную ранее при обработке запроса с порядковым номером T (запросы нумеруются с 1)
// 2) Если запрос с номером T был отклонен, то текущ запрос на освобождение памяти игнорируется


// ========= 1. Считывание задачи (читает M запросов) ========= //
void ReadVecRequest(std::vector<int>* arr_req)
{
    int M, cur_number;
    std::cin >> M;

    for (int i_req = 0; i_req < M; ++i_req)
    {
        std::cin >> cur_number;
        arr_req->push_back(cur_number);
    }
}

// ========= 2. Обработка запросов ========= //
void StartRequests(const std::vector<int>& req_arr, std::vector<int>* output_vec, MemManager* allocator)
{
    // 1. Итерируется по всем запросам
    for (std::vector<int>::const_iterator it = req_arr.begin(); it != req_arr.end(); ++it)
    {
        // Для полож запросов вызывает allocateMemory и сохраняет результат (номер 1ой яч или 0 при отказе)
        // Для отрицат запросов вызывает FreeMemory с номером запроса (переводит отрицат число в полож)
        if (*it > 0)
            output_vec->push_back(allocator->AllocateMemory(*it));
        if (*it < 0)
            allocator->FreeMemory(-(*it));
    }
}

// ========= 3. Выводит рез-ты обработки запросов на выделение памяти ========= //
void Output(const std::vector<int>& vec)
{
    for (std::vector<int>::const_iterator it = vec.begin(); it != vec.end(); ++it)
        printf("%d\n", *it);
}

int main()
{
    int N;                        // Кол-во яч памяти N
    std::cin >> N;
    MemManager manager_mem(N);    // Создаем менеджер памяти с N яч
    std::vector<int> req_arr;
    ReadVecRequest(&req_arr);

    std::vector<int> res_vec;
    StartRequests(req_arr, &res_vec, &manager_mem);
    Output(res_vec);
    return 0;
}
