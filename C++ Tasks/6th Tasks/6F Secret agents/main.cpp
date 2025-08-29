#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>

#include "Independent_union_set.h"


std::vector<std::pair<int64_t, std::pair<int, int>>> Calculate_distance_btw_agent_sorted(size_t n, std::vector<std::pair<int64_t, int64_t>>& coord_agent_vec)
{
    std::vector<std::pair<int64_t, std::pair<int, int>>> pair_distance_indexAgentes;

    for (size_t first_agent = 0; first_agent < n; ++first_agent)
    {
        for (size_t second_agent = first_agent + 1; second_agent < n; ++second_agent)
        {
            int64_t coord_1st_x = coord_agent_vec[first_agent].first;
            int64_t coord_2st_x = coord_agent_vec[second_agent].first;
            int64_t coord_1st_y = coord_agent_vec[first_agent].second;
            int64_t coord_2st_y = coord_agent_vec[second_agent].second;
            int64_t distance = (coord_1st_x - coord_2st_x) * (coord_1st_x - coord_2st_x) + (coord_1st_y - coord_2st_y) * (coord_1st_y - coord_2st_y);

            pair_distance_indexAgentes.push_back(std::make_pair(distance, std::make_pair(first_agent, second_agent)));
        }
    }

    std::sort(pair_distance_indexAgentes.begin(), pair_distance_indexAgentes.end());

    return pair_distance_indexAgentes;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    long double res = 0;

    size_t n = 0;
    std::cin >> n;

    std::vector<std::pair<int64_t, int64_t>> coord_agent_vec(n);
    for (size_t i_agent = 0; i_agent < n; ++i_agent)
    {
        int64_t tmp_coord_x = 0, tmp_coord_y = 0;
        std::cin >> tmp_coord_x >> tmp_coord_y;

        coord_agent_vec[i_agent] = std::make_pair(tmp_coord_x, tmp_coord_y);
    }

    Independent_union_set set_independent_union(n);
    int64_t tmp_max_distance = -1;
    std::vector<std::pair<int64_t, std::pair<int, int>>> pair_distance_indexAgentes = Calculate_distance_btw_agent_sorted(n, coord_agent_vec);

    for (size_t i_agent = 0; i_agent < pair_distance_indexAgentes.size(); ++i_agent)
    {
        int root_set_1st = set_independent_union.Get_root_of_set(pair_distance_indexAgentes[i_agent].second.first);
        int root_set_2st = set_independent_union.Get_root_of_set(pair_distance_indexAgentes[i_agent].second.second);

        if (root_set_1st != root_set_2st)
            tmp_max_distance = pair_distance_indexAgentes[i_agent].first;

        set_independent_union.Union_set(root_set_1st, root_set_2st);
    }

    res = sqrt(tmp_max_distance);

    std::cout.precision(10);
    std::cout << std::fixed;
    std::cout << res << '\n';

    return 0;
}