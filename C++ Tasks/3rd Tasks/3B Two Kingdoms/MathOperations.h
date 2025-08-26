#pragma once

#include <iostream>

// ========= ������� {(p_value^degree) mod prime_value}, ��������� ����� �������� ����������: O(log degree) ========= //
int64_t p_binFastExp(int64_t p_value, int degree, int64_t prime_value);
