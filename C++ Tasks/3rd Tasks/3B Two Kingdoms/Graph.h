#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <list>
#include <utility>
#include <algorithm>

#include "VertexHash.h"

// ========= ����� ����� (������������ ��� ������ � �������): �������� ������� ��������� ========= //
class Graph
{
public:
    // �����������: _G ����������������� -> ������ ��������������� ���� (��. Init_DFS)
    Graph(const std::vector<std::vector<int>>& _G, const int _root = 0);

    int GetRoot() const { return root; }

    // ��������� ���� ���� ����������� ������� v.
    // ��������� ��������������� ��� ������� �� �������: h(v) = deg(v) + h(c1) * prime^len1 + ... 
    // (�1 ���������, len1 ���-�� ������ � ���������)
    VertexHash Concatenate(int v, std::vector<std::pair<VertexHash, int>> _subHashTable);

    // ��������� ���� ���� ����������� (���������, ����� �����)
    void Init_DFShashTable(int v);

    // ������ ����������� ������
    void Init_ParamHashes(int64_t _p, int64_t _prime);

    int64_t Hash_func();

    // ������ �������� ����: ������������ ���� � �������� �������.
    std::vector<std::vector<int>> Reverse_G(const std::vector<std::vector<int>>& _G);

    // �������� ���� �������� ������� v � ���� ������.
    void Init_listVert(int v, std::vector<int>* correctVert_list);

    // �������� Subsize_DFS(...) ��� ����������� �������� ���� �����������
    // ���� ��������� � �������, �������� ������� ��������� ������ �� ���������� �� ������ n / 2.
    // ���� ����� ����, ������ ������ ����� ����, ��� �� � ������.
    // ���� ������� ���, ��������� ������������� �������, ���������� � ������ ��������, � ������ � ������.
    Graph Rebuild_centroidal();

private:
    // ������ ������ ������ �� ������ �������� ������ ���������: ������� ���� � �������� (����������)
    void Init_DFS(const int v, const std::vector<std::vector<int>>& _G, const int _parent = -1);

    // ��������� ������� ���� ����������� (����������)
    void Subsize_DFS(const int v, bool isInit = false);

    int root;                               // ������ ������
    int n;                                  // ���-�� ������
    std::vector<std::vector<int>> G;        // ������ ��������� � ������� (����)

    std::vector<int> size_sub;              // ������� �����������
    std::vector<VertexHash> hashes_vec;     // ���� �����������

    int64_t p_val = 2, prime_val = 1e9 + 7; // ��������� ��� ���-�������
};
