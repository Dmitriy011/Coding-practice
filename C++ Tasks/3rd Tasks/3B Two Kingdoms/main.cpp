#include <iostream>
#include <cmath>
#include <vector>
#include <list>
#include <utility>
#include <algorithm>

#include "MathOperations.h"
#include "Graph.h"

// ========= 1. Считывание задачи (N и 2 графа) ========= //
// P.s: G считывается как неор, потому что каждое ребро a — b доб в оба списка смежности
void Input(int* N, std::vector<std::vector<int>>* G_y, std::vector<std::vector<int>>* G_x, std::istream& in_stream = std::cin)
{
    in_stream >> *N;
    G_y->resize(*N);
    G_x->resize(*N);

    int v_a = 0;
    int v_b = 0;

    for (int i = 0; i + 1 < *N; ++i)
    {
        in_stream >> v_a;
        in_stream >> v_b;

        (*G_y)[v_a - 1].push_back(v_b - 1);
        (*G_y)[v_b - 1].push_back(v_a - 1);
    }

    for (int i = 0; i + 1 < *N; ++i)
    {
        in_stream >> v_a;
        in_stream >> v_b;

        (*G_x)[v_a - 1].push_back(v_b - 1);
        (*G_x)[v_b - 1].push_back(v_a - 1);
    }
}

// ========= 2. Решение задачи ========= //
std::vector<int> Desicion(int N, std::vector<std::vector<int>>* G_y, std::vector<std::vector<int>>* G_x)
{   
    // 1. Преобразование неор G в направленное дерево от корня (корень - центроид)
    // Если центроида два, то создается фиктивная вершина 
    Graph Y_centroidal = Graph(*G_y).Rebuild_centroidal();
    G_y->clear();
    Graph X_centroidal = Graph(*G_x).Rebuild_centroidal();
    G_x->clear();

    // 2. Построение хешей поддеревьев.
    // Используется рекурсивный DFS, в котором: a) Строятся хеши детей 2) Хеш текущей v вычисляется через конкатенацию детских хешей + длины
    int64_t hash1_root = Y_centroidal.Hash_func();
    int64_t hash2_root = X_centroidal.Hash_func();

    // 3. Если хеши разные, значит деревья не изоморфны
    if (hash1_root != hash2_root)
        return std::vector<int>({ -2 });

    // 4. Восстановление соответствия вершин (биекция)
    // Создаются списки обхода вершин от корня для каждого G.
    std::vector<int> Y_listGraph;
    std::vector<int> X_listGraph;
    Y_centroidal.Init_listVert(Y_centroidal.GetRoot(), &Y_listGraph);
    X_centroidal.Init_listVert(X_centroidal.GetRoot(), &X_listGraph);

    // 5. Построение ответа
    // res[u] = v означает, что вершина u из Y соответствует вершине v из X.
    std::vector<int> res(Y_listGraph.size());
    for (size_t i = 0; i < Y_listGraph.size(); ++i)
        res[Y_listGraph[i]] = X_listGraph[i];

    return res;
}

// ========= 3. Вывод ответа (i-ый элемент - это новый номер i-го города) ========= //
void Write(const int N, const std::vector<int>& res_vec, std::ostream& out_stream = std::cout)
{
    for (size_t i = 0; i < std::min((size_t)N, res_vec.size()); ++i)
        out_stream << res_vec[i] + 1 << "\n";
}

// ========= MAIN ========= //
int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    int N;
    std::vector<std::vector<int>> G_y;
    std::vector<std::vector<int>> G_x;
    Input(&N, &G_y, &G_x);

    std::vector<int> res = Desicion(N, &G_y, &G_x);
    Write(N, res);
}