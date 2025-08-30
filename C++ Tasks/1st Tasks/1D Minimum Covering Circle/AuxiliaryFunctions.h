#pragma once

#include <iostream>
#include <vector>

#include "Point.h"

extern const double eps;

// ========= Находит интервал [L, R] по X, в котором должен лежать центр окружности радиуса к, чтобы эта точка попала в круг: ========= //
std::pair<double, double> Intervalx_IncludingPoint(StructPoint point, double r);

// ========= Проверить, можно ли найти такой центр круга на оси Ox, чтобы при данном r накрыть хотя бы k точек ========= //
bool isContained_kPoints(const std::vector<StructPoint>& points, size_t k, double r);