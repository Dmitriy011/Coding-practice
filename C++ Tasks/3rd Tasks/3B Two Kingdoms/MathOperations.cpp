#include "MathOperations.h"

// ========= ������� {(p_value^degree) mod prime_value}, ��������� ����� �������� ����������: O(log degree) ========= //
int64_t p_binFastExp(int64_t p_value, int degree, int64_t prime_value)
{
    int64_t res = 1;

    // 1. ���� ������� degree ������ 0
    while (degree)
    {
        // 1.1. ���� ��������� ��� ������� ����� 1 (�� ���� ������� �����): ����� p_value ����� ������ � ���-��
        if (degree & 1)
        {
            // 1.1.1. �������� ��������� �� p_value, ����� �� ������ (����� �� ���� ������������).
            res *= p_value;
            res %= prime_value;
        }

        // 1.2. ������� p_value � ���������� ����: 
        // �� ������ �� �� �������� p_value � ������� � �� ����, ��������� �� ��������: 1, 2, 4, 8, ...
        p_value = (p_value * p_value) % prime_value;

        // 1.3. ����� ������� �� 2 (��������� � ���� ���� � ����������)
        degree >>= 1;
    }

    return res;
}

// ������:
// 5 = 101; 3^5 mod 7 ( p = 3, deg = 5)

// 0) res = 1 -> 
//      res *= 3 = 3
//      p = 3^2 = 9 % 7 = 2
//      deg = 2
// 1) �������: ��� = 0
// 2) ��������� ��� -> 
//      res *= 4  = 12 % 7 = 5
// �����: 5
