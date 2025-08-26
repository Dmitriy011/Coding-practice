#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <list>
#include <utility>
#include <algorithm>

#include "VertexHash.h"

// ========= Класс Графа (предназначен для работы с деревом): построен списком смежности ========= //
class Graph
{
public:
    // Конструктор: _G неориентированный -> Строит ориентированный граф (см. Init_DFS)
    Graph(const std::vector<std::vector<int>>& _G, const int _root = 0);

    int GetRoot() const { return root; }

    // Сортирует хеши всех поддеревьев текущей v.
    // Вычисляет комбинированный хеш вершины по формуле: h(v) = deg(v) + h(c1) * prime^len1 + ... 
    // (с1 поддерево, len1 кол-во вершин в поддереве)
    VertexHash Concatenate(int v, std::vector<std::pair<VertexHash, int>> _subHashTable);

    // Вычисляет хеши всех поддеревьев (построчно, снизу вверх)
    void Init_DFShashTable(int v);

    // Запуск хеширования дерева
    void Init_ParamHashes(int64_t _p, int64_t _prime);

    int64_t Hash_func();

    // Создаёт обратный граф: направленные рёбра в обратную сторону.
    std::vector<std::vector<int>> Reverse_G(const std::vector<std::vector<int>>& _G);

    // Собирает всех потомков вершины v в один список.
    void Init_listVert(int v, std::vector<int>* correctVert_list);

    // Вызывает Subsize_DFS(...) для определения размеров всех поддеревьев
    // Ищет центроиды — вершины, удаление которых разбивает дерево на компоненты не больше n / 2.
    // Если центр один, просто создаёт новый граф, где он — корень.
    // Если центров два, добавляет искусственную вершину, соединённую с обоими центрами, и делает её корнем.
    Graph Rebuild_centroidal();

private:
    // Создаёт ориент дерево на основе неориент списка смежности: убирает рёбра к родителю (Рекурсивно)
    void Init_DFS(const int v, const std::vector<std::vector<int>>& _G, const int _parent = -1);

    // Вычисляет размеры всех поддеревьев (Рекурсивно)
    void Subsize_DFS(const int v, bool isInit = false);

    int root;                               // Корень дерева
    int n;                                  // Кол-во вершин
    std::vector<std::vector<int>> G;        // Список смежности — потомки (дети)

    std::vector<int> size_sub;              // Размеры поддеревьев
    std::vector<VertexHash> hashes_vec;     // Хеши поддеревьев

    int64_t p_val = 2, prime_val = 1e9 + 7; // Параметры для хеш-функции
};
