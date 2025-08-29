#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>

#include "Graph.h"
#include "DFS.h"

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int res = 0;

    int n = 0;
    int m = 0;

    std::cin >> n >> m;

    Graph G(n);
    for (int i_road = 0;  i_road < m; ++i_road)
    {
        int st_city = 0;
        int fn_city = 0;
        int cost_break_road = 0;

        std::cin >> st_city >> fn_city >> cost_break_road;

        --st_city;
        --fn_city;

        G.AddEdge(st_city, fn_city, cost_break_road);
    }

    G.vert_used = std::vector<bool>(n, false);
    G.cur_time_traversal = 0;
    G.tmp_time_traversal = std::vector<int>(n, 0);
    G.tmp_vec_search = std::vector<int>(n, 0);

    int min_cost_edge = -1;
    for (int index_vert = 0; index_vert < n; ++index_vert)
    {
        if (G.vert_used[index_vert] == false)
        {
            auto func_used_vert = [&min_cost_edge](int cost_to_use)
            {
                if (min_cost_edge < 0 || min_cost_edge > cost_to_use)
                    min_cost_edge = cost_to_use;
            };

            int parent_vert = -1;
            DFS(index_vert, parent_vert, G, func_used_vert);
        }
    }

    res = min_cost_edge;
    std::cout << res << '\n';

    return 0;
}
