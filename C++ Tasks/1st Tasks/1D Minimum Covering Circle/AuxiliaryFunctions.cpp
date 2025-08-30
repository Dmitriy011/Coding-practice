#include <algorithm>

#include "AuxiliaryFunctions.h"


std::pair<double, double> Intervalx_IncludingPoint(StructPoint point, double r)
{
//**** 1) (x - cx)² + y² ≤ R²; 
//**** 1) cx ∈ [x - std::sqrt(std::fabs(R² - y²));]

    double gap = std::sqrt(std::fabs(r * r - point.y * point.y));

    //1)  
    return std::make_pair(point.x - gap, point.x + gap);
}

bool isContained_kPoints(const std::vector<StructPoint>& points, size_t k, double r)
{
    //**** 1) Обход всех точек + Если по y точка дальше, чем r — она не может быть накрыта никаким кругом с центром на Ox и радиусом r ->  пропускаем её.
    //**** 2) Для подходящих точек:
    //**** 3) Каждая подходящая точка даёт интервал возможных положений центра круга.
    //**** 4) x, false (начало интервала) 
    //**** 5) x, true (конец)
    //**** 6) Сортируем по x по возрастанию
    //**** 7) Подсчёт "накрытых" точек при проходе. "Двигаем" центр окружности вдоль оси Ox.
    //**** 8) counter: Сколько интервалов сейчас накрывают текущ позицию центра (т.е. сколько открыто)

    std::vector<std::pair<double, bool>> x_isInside;
    x_isInside.reserve(2 * points.size());

    // 1) 
    for (size_t i_point = 0; i_point < points.size(); ++i_point)
    {
        // 2) 
        if (std::abs(points[i_point].y) < r + eps)
        {
            // 3) 
            std::pair<double, double> res = Intervalx_IncludingPoint(points[i_point], r);

            // 4) 
            x_isInside.emplace_back(res.first, false);
            // 5) 
            x_isInside.emplace_back(res.second, true);
        }
    }

    // 6)
    std::sort(x_isInside.begin(), x_isInside.end());

    // 7)
    size_t counter = 0;
    for (size_t i_point = 0; i_point < x_isInside.size(); ++i_point)
    {
        if (x_isInside[i_point].second)
            counter--;
        else
            counter++;

        if (counter == k)
            return true;
    }

    return false;
}
