#include "Graph.h"
#include "MathOperations.h"

void Graph::Init_DFS(const int v, const std::vector<std::vector<int>>& _G, const int _parent)
{
    for (int to : _G[v])
    {
        // Исключает обратное ребро к родителю, чтобы избежать циклов.
        if (to == _parent)
            continue;

        G[v].push_back(to);
        Init_DFS(to, _G, v);
    }
}

void Graph::Subsize_DFS(const int v, bool isInit)
{
    if (isInit)
        size_sub.assign(n, 1);

    for (int to : G[v])
    {
        Subsize_DFS(to);

        // Для каждой вершины прибавляет размеры всех её потомков
        size_sub[v] += size_sub[to];
    }
}

Graph::Graph(const std::vector<std::vector<int>>& _G, const int _root)
{
    root = _root;
    n = _G.size();

    G.resize(n);
    Init_DFS(_root, _G);
}

// Идея: представить структуру дерева (или поддерева) как одно число (хеш), которое можно сравнивать с другими деревьями.
VertexHash Graph::Concatenate(int v, std::vector<std::pair<VertexHash, int>> _subHashTable)
{
    // Нач знач хеша — кол-во детей v
    int64_t hash = G[v].size();

    // Сортирует хеши всех поддеревьев (чтобы структурно одинаковые деревья всегда давали один и тот же хеш, независимо от порядка обхода)
    std::sort(_subHashTable.begin(), _subHashTable.end());

    // Длина поддерева (включая v)
    int len = 1;
    for (size_t i_child = 0; i_child < _subHashTable.size(); ++i_child)
    {
        VertexHash cur_hash = _subHashTable[i_child].first;
        len += cur_hash.len;
        hash = (hash + cur_hash.hash_v * p_binFastExp(p_val, len - 1, prime_val)) % prime_val;
    }

    std::vector<int> indexes;

    // _subHashTable[i] - first: VertexHash дочерней v (хеш её поддерева), second: int, индекс этой дочерней v.
    // Т.е: сортируем _subHashTable по хешам (выше по коду), потом в том же отсортированном порядке собираем номера дочерних v.
    for (size_t i_child = 0; i_child < _subHashTable.size(); ++i_child)
        indexes.push_back(_subHashTable[i_child].second);

    // Теперь: G[v] — перезаписываем этот список, упорядочив его так, чтобы соответствовать отсортированным хешам.
    G[v] = indexes;

    // Хеш текущего поддерева и длинна
    return VertexHash(len, hash);
}

std::vector<std::vector<int>> Graph::Reverse_G(const std::vector<std::vector<int>>& _G)
{
    std::vector<std::vector<int>> tmp_G = _G;
    for (size_t v = 0; v < _G.size(); ++v)
    {
        for (int to : _G[v])
            tmp_G[to].push_back(v);
    }

    return tmp_G;
}

void Graph::Init_listVert(int v, std::vector<int>* correctVert_list)
{
    correctVert_list->push_back(v);

    for (int to : G[v])
        Init_listVert(to, correctVert_list);
}

void Graph::Init_DFShashTable(int v)
{
    if (G[v].size() == 0)
        return;

    std::vector<std::pair<VertexHash, int>> sub_hashes;

    for (int to : G[v])
    {
        Init_DFShashTable(to);
        sub_hashes.push_back(std::make_pair(hashes_vec[to], to));
    }

    hashes_vec[v] = Concatenate(v, sub_hashes);
}

void Graph::Init_ParamHashes(int64_t _p, int64_t _prime)
{
    p_val = _p;
    prime_val = _prime;
}

Graph Graph::Rebuild_centroidal()
{
    // 1. Вычисляются размеры поддеревьев
    Subsize_DFS(root, true);
    std::vector<int> centroids;

    // 2. Ищутся центроид(ы): v, у которой размеры всех её поддеревьев не превышают n/2
    for (int v = 0; v < n; ++v)
    {
        // Размер поддерева текущей вершины v не меньше n/2; Иначе точно не центроид
        if (2 * size_sub[v] < n)
            continue;

        bool isCentroidCandidate = true;
        for (int to : G[v])
        {
            if (2 * size_sub[to] > n)
            {
                isCentroidCandidate = false;
                break;
            }
        }

        if (isCentroidCandidate)
            centroids.push_back(v);
    }

    if (centroids.size() == 1)
        return Graph(Reverse_G(G), centroids[0]);

    int v_a = centroids[0];
    int v_b = centroids[1];
    G.push_back(std::vector<int>({}));
    G[n].push_back(v_a);
    G[n].push_back(v_b);

    for (std::vector<int>::iterator it = G[v_a].begin(); it != G[v_a].end(); ++it)
    {
        if (*it == v_b)
        {
            G[v_a].erase(it);
            break;
        }
    }

    for (std::vector<int>::iterator it = G[v_b].begin(); it != G[v_b].end(); ++it)
    {
        if (*it == v_a)
        {
            G[v_b].erase(it);
            break;
        }
    }

    return Graph(Reverse_G(G), n);
}

int64_t Graph::Hash_func()
{
    Init_ParamHashes(1000003, 1000000009);
    hashes_vec.resize(n);
    Init_DFShashTable(root);

    return hashes_vec[root].hash_v;
}