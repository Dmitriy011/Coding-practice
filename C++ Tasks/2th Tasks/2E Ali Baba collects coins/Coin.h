#pragma once

struct Coin
{
//* pos ��������� ������
//* time ������� � ��� (�����, �� �������� ������ ���� �������)

    int32_t pos;   
    int32_t time;  

    //* ���������� ����� ������� �� �����, ����� �� �������� (���� ����� ���������).
    bool operator<(Coin rhs) const
    {
        return std::make_pair(pos, time) < std::make_pair(rhs.pos, rhs.time);
    }

    //* �������� 2�� ����� ��� �������� (������������ � DP, ��� pos � time ����� ������������� ��� ���� � ����� ����)
    Coin operator+(Coin rhs) const
    {
        return { pos + rhs.pos, time + rhs.time };
    }
};
