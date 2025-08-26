#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <list>
#include <utility>
#include <algorithm>

// ========= ������������� ���� ��������� ========= //
class VertexHash
{
public:
    int64_t hash_v; // ��� ��������� � ����� ������� v
    int len;        // ���-�� ������� � ���������

    // �� �����: ����� 1 (��� ����), ��� 0.
    VertexHash();

    // ���������������� �����������: ��������� ����� � ���.
    VertexHash(int _len, int64_t _hash);

    // ��������� ����������� ������� VertexHash �� hash_val
    bool operator < (const VertexHash& rhs) const { return this->hash_v < rhs.hash_v; } 
};
