#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>
#include <utility>

// n - количество точек
// k - количество точек, которые должны быть внутри круга

const double eps = 1e-6;

struct StructPoint
{
    int x, y;
};

// - Находит интервал [L, R] по X, в котором должен лежать центр окружности радиуса к, чтобы эта точка попала в круг: --//
std::pair<double, double> Intervalx_IncludingPoint(StructPoint point, double r)
{
    double gap = std::sqrt(std::fabs(r * r - point.y * point.y));

    // (x - cx)² + y² ≤ R²
    // cx ∈ [x - std::sqrt(std::fabs(R² - y²));]
    return std::make_pair(point.x - gap, point.x + gap);
}

// Проверить, можно ли найти такой центр круга на оси Ox, чтобы при данном r накрыть хотя бы k точек.
bool isContained_kPoints(const std::vector<StructPoint>& points, size_t k, double r)
{
    std::vector<std::pair<double, bool>> x_isInside;
    x_isInside.reserve(2 * points.size());

    // Обход всех точек + Если по y точка дальше, чем r — она не может быть накрыта никаким кругом с центром на Ox и радиусом r ->  пропускаем её.
    for (size_t No_point = 0; No_point < points.size(); ++No_point)
    {
        // Для подходящих точек:
        if (std::abs(points[No_point].y) < r + eps)
        {
            std::pair<double, double> res = Intervalx_IncludingPoint(points[No_point], r);  // Каждая подходящая точка даёт интервал возможных положений центра круга.

            x_isInside.emplace_back(res.first, false);                                      // x, false (начало интервала) 
            x_isInside.emplace_back(res.second, true);                                      // x, true (конец)
        }
    }

    // Сортируем по x по возрастанию
    std::sort(x_isInside.begin(), x_isInside.end());

    // Подсчёт "накрытых" точек при проходе
    // "Двигаем" центр окружности вдоль оси Ox.
    size_t counter = 0;                                                         // Сколько интервалов сейчас накрывают текущ позицию центра 
    for (size_t i_point = 0; i_point < x_isInside.size(); ++i_point)         // (т.е. сколько открыто)
    {
        if (x_isInside[i_point].second == true)
            counter--;
        else
            counter++;

        if (counter == k)
            return true;
    }

    return false;
}

// -- Поиск минимального возможного радиуса-- //
double find_smallestRadiusCircle(const std::vector<StructPoint>& points, size_t k_countPointsInCircle)
{
    const double L = 0.;
    const double R = std::sqrt(2 * 2000. * 2000.); //  Макс возможн. радиус
    double mid = (L + R) / 2.;

    // На каждой итерации проверяем: можно ли при текущем mid накрыть k точек?
    // Бинарный поиск по вещественному числу.
    for (double L_hs = L, R_hs = R; L_hs + eps < R_hs; mid = (L_hs + R_hs) / 2.)
    {
        // Если при данном радиусе можно накрыть k точек - уменьшаем радиус (ищем меньше).
        // Если нельзя накрыть - значит, текущий радиус mid слишком маленький - его нужно увеличить, поэтому сдвигаем левую границу
        if (isContained_kPoints(points, k_countPointsInCircle, mid) == true)
            R_hs = mid;
        else
            L_hs = mid;
    }

    return mid;
}

int main()
{
    // -- Считывание задачи --//
    size_t n;
    size_t k;

    std::cin >> n >> k;

    std::vector<StructPoint> points(n);
    for (size_t No_point = 0; No_point < points.size(); ++No_point)
    {
        std::cin >> points[No_point].x >>
            points[No_point].y;
    }

    // -- Решение задачи --//
    std::cout << std::setprecision(6) << std::fixed << find_smallestRadiusCircle(points, k) << "\n";

    return 0;
}
