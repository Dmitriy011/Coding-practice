#include <iostream>
#include <vector>
#include <algorithm>

#include "Game.h"
#include "ResGame.h"
#include "Graph.h"

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int32_t res = 0;

    int32_t size = 0;
    int32_t m = 0;

    std::cin >> size >> m;

    std::vector<Game> games_vec(m);

    int32_t number_1st = 0;
    int32_t number_2st = 0;
    Res_game res_match;
    for (int i_game = 0; i_game < m; ++i_game)
    {
        std::cin >> number_1st >> number_2st;

        int32_t number_win;
        std::cin >> number_win;
        if (number_win == 1)
            res_match = first;
        else
        {
            if (number_win == 2)
                res_match = second;
            else
                res_match = draw;
        }

        games_vec.push_back({ number_1st, number_2st, res_match });

        number_1st = 0;
        number_2st = 0;
    }

    Graph G(size, games_vec);
    Graph graph_revers(size, games_vec, true);
    G.info_componentsConnection = G.GetInfoComponentConnections(graph_revers);
    std::vector<int32_t> clever_component_sizes;

    for (size_t v = 0; v < G.info_componentsConnection.is_clever_component_connection_vec.size(); ++v)
    {
        bool is_clever = G.info_componentsConnection.is_clever_component_connection_vec[v];
        if (is_clever)
            clever_component_sizes.push_back(G.info_componentsConnection.size_componentsConnective[v]);
    }

    int32_t min_val = *std::min_element(clever_component_sizes.begin(), clever_component_sizes.end());
    res = size + 1 - min_val;
    std::cout << res << '\n';

    return 0;
}
