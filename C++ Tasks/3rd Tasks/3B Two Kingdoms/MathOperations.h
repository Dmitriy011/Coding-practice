#pragma once

#include <iostream>

// ========= Ѕыстрое {(p_value^degree) mod prime_value}, использу€ метод бинарной экспоненты: O(log degree) ========= //
int64_t p_binFastExp(int64_t p_value, int degree, int64_t prime_value);
