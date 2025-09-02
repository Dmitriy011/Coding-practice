#include <vector>
#include <algorithm>

#include "AuxiliaryFunctions.h"

std::vector<unsigned>::iterator find_pivot(std::vector<unsigned>::iterator L, std::vector<unsigned>::iterator R)
{
    //* mid: �������� �� �������� ��������� [L, R)

    std::vector<unsigned>::iterator mid = L + (R - L) / 2;
    --R;

    if (*mid < *L)
        std::swap(mid, L);

    if (*mid < *R)
        return mid;

    if (*L < *R)
        return R;

    return L;
}

std::vector<unsigned>::iterator partition(std::vector<unsigned>::iterator L, std::vector<unsigned>::iterator R, std::vector<unsigned>::iterator pivot)
{
//**** 1) ���� ���� �������� ��-�

// * tmp_begin � ��� ������ �������
// * R - ��������� �� ��������� ��

//**** 2) ��, ��������� ������
//**** 3) ��, ��������� �����. 
//**** �����: ������������ ��-��, ���� �� �������� �������

//**** 5) L == R + 2 � ��������, ��� ���� "����������" �� 2 �������
//**** L - 1 != tmp_begin � �������� �� ����, ����� partition �������� ������ ���� �� (� ������)
//**** ���� ��� ���� ���: ������������ �������� �������, �.�. ��� �������� � ���� �������� �� ����������
//**** [5, 5, 5, 5, 5] -> L ��������� ������ -> R == 1, L == 3 -> ������� L - 1 = 2

    // 1) 
    unsigned pivot_value = *pivot;
    std::vector<unsigned>::iterator tmp_begin = L;

    --R;
    while (L <= R)
    {
        // 2) 
        if (*L < pivot_value)
            ++L;
        else
        {
            // 3) 
            if (pivot_value < *R)
                --R;
            else
            {
                std::iter_swap(L, R);

                ++L;
                --R;
            }
        }
    }

    // 5) 
    if (L == R + 2 && L - 1 != tmp_begin)
        return L - 1;

    return L;
}
