#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <list>
#include <utility>
#include <algorithm>

// ========= Представления хеша поддерева ========= //
class VertexHash
{
public:
    int64_t hash_v; // Хэш поддерева с текущ веришны v
    int len;        // Кол-во вершины в поддереве

    // По умолч: длина 1 (сам узел), хеш 0.
    VertexHash();

    // Пользовательский конструктор: принимает длину и хеш.
    VertexHash(int _len, int64_t _hash);

    // Позволяет сортировать объекты VertexHash по hash_val
    bool operator < (const VertexHash& rhs) const { return this->hash_v < rhs.hash_v; } 
};
