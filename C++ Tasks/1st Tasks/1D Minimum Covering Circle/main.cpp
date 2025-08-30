#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>
#include <utility>

#include "Point.h"
#include "AuxiliaryFunctions.h"


const double eps = 1e-6;

// =========  Поиск минимального возможного радиуса ========= //
double find_smallestRadiusCircle(const std::vector<StructPoint>& points, size_t k_countPointsInCircle)
{
//**** 0) R: Макс возможн. радиус
//**** 1) На каждой итерации проверяем: можно ли при текущем mid накрыть k точек? Бинарный поиск по вещественному числу.
//**** 2) Если при данном радиусе можно накрыть k точек - уменьшаем радиус (ищем меньше). Если нельзя накрыть - значит, текущий радиус mid слишком маленький - его нужно увеличить, поэтому сдвигаем левую границу

    const double L = 0.;
    const double R = std::sqrt(2 * 2000. * 2000.); 
    double mid = (L + R) / 2.;

    // 1)
    for (double L_hs = L, R_hs = R; L_hs + eps < R_hs; mid = (L_hs + R_hs) / 2.)
    { 
    // 2) 
        if (isContained_kPoints(points, k_countPointsInCircle, mid))
            R_hs = mid;
        else
            L_hs = mid;
    }

    return mid;
}

//* n - количество точек
//* k - количество точек, которые должны быть внутри круга

int main()
{
// ========= 2. Считывание задачи ========= //
    size_t n, k;
    std::cin >> n >> k;

    std::vector<StructPoint> points(n);
    for (size_t i_point = 0; i_point < points.size(); ++i_point)
        std::cin >> points[i_point].x >> points[i_point].y;

// ========= 2. Решение задачи ========= //
    std::cout << std::setprecision(6) << std::fixed << find_smallestRadiusCircle(points, k) << "\n";

    return 0;
}
