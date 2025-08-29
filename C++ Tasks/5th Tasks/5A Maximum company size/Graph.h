#pragma once

#include <vector>

#include "Game.h"
#include "ResGame.h"

class Graph
{
public:
    struct ComponentsConnectiveInGraph
    {
        std::vector<int32_t> size_componentsConnective;
        std::vector<bool> is_clever_component_connection_vec;

        ComponentsConnectiveInGraph() = default;
    };

    int32_t size;
    std::vector<std::vector<int32_t>> G;
    ComponentsConnectiveInGraph info_componentsConnection;

    explicit Graph(const int32_t _size, const std::vector<Game>& games_vec, bool isReverse = false) : size(_size), G(_size)
    {
        InitGameStory(games_vec, isReverse);
    }

    ComponentsConnectiveInGraph GetInfoComponentConnections(const Graph& reversed_graph)
    {
        int32_t n = this->G.size();
        std::vector<bool> is_use_vert_vec(n, false);
        std::vector<int32_t> order_search;

        for (int v = 0; v < n; ++v)
        {
            if (is_use_vert_vec[v])
                continue;

            auto tmp_func_st_vert = [&is_use_vert_vec](const int32_t v)
            {
                is_use_vert_vec[v] = true;
            };

            auto tmp_func_fn_vert = [&order_search](const int32_t v)
            {
                order_search.push_back(v);
            };

            auto tmp_func_check_used = [&is_use_vert_vec](const int32_t v)
            {
                return is_use_vert_vec[v];
            };

            DFS(*this, v, tmp_func_st_vert, tmp_func_fn_vert, tmp_func_check_used);
        }

        is_use_vert_vec.assign(n, false);
        std::vector<int32_t> component_conntections_vec(n);
        std::vector<int32_t> size_component_connection_vec;
        int32_t tmp_cur_component = -1;
        for (int32_t i = static_cast<int32_t>(order_search.size()) - 1; i >= 0; --i)
        {
            int32_t index_vert = order_search[i];

            if (is_use_vert_vec[index_vert])
                continue;

            ++tmp_cur_component;
            size_component_connection_vec.push_back(0);

            auto tmp_func_st_vert = [&is_use_vert_vec, &component_conntections_vec, &tmp_cur_component, &size_component_connection_vec](const int32_t v)
            {
                is_use_vert_vec[v] = true;
                component_conntections_vec[v] = tmp_cur_component;
                ++size_component_connection_vec.back();
            };

            auto tmp_func_fn_vert = [](const int32_t v) {};

            auto tmp_func_used_vert = [&is_use_vert_vec](const int32_t v)
            {
                return is_use_vert_vec[v];
            };

            DFS(reversed_graph, index_vert, tmp_func_st_vert, tmp_func_fn_vert, tmp_func_used_vert);
        }

        std::vector<bool> is_clever_component_connection_vec(size_component_connection_vec.size(), true);

        for (int v = 0; v < n; ++v)
        {
            std::vector<int32_t> tmp_cur_neighbour_vec = this->G[v];
            for (size_t i_neighbour = 0; i_neighbour < tmp_cur_neighbour_vec.size(); ++i_neighbour)
            {
                int32_t tmp_clever_component_connection = component_conntections_vec[v];
                int32_t tmp_stup_component_connection = component_conntections_vec[tmp_cur_neighbour_vec[i_neighbour]];

                if (tmp_clever_component_connection != tmp_stup_component_connection)
                    is_clever_component_connection_vec[tmp_stup_component_connection] = false;
            }
        }

        return ComponentsConnectiveInGraph{ size_component_connection_vec, is_clever_component_connection_vec };
    }


private:
    void InitGameStory(const std::vector<Game>& games_vec, bool is_reverse = false)
    {
        bool tmp_1st_condition = false;
        bool tmp_2st_condition = false;
        for (size_t i_game = 0; i_game < games_vec.size(); ++i_game)
        {
            tmp_1st_condition = (games_vec[i_game].res == first && !is_reverse);
            tmp_2st_condition = (games_vec[i_game].res == second && is_reverse);
            if (tmp_1st_condition == true || tmp_2st_condition == true)
                G[games_vec[i_game].number_1st - 1].push_back(games_vec[i_game].number_2st - 1);
            else
            {
                tmp_1st_condition = (games_vec[i_game].res == second && !is_reverse);
                tmp_2st_condition = (games_vec[i_game].res == first && is_reverse);
                if (tmp_1st_condition == true || tmp_2st_condition == true)
                    G[games_vec[i_game].number_2st - 1].push_back(games_vec[i_game].number_1st - 1);
            }
        }
    }

    template <typename Tmp1Type, typename Tmp2Type, typename Tmp3Type>
    void DFS(const Graph& graph, const int32_t index_vert, Tmp1Type func_st_vert, Tmp2Type func_fn_vert, Tmp3Type func_is_used_vert)
    {
        func_st_vert(index_vert);

        std::vector<int32_t> tmp_cur_neighbors = graph.G[index_vert];
        for (size_t v = 0; v < tmp_cur_neighbors.size(); ++v)
        {
            if (!func_is_used_vert(tmp_cur_neighbors[v]))
                DFS(graph, tmp_cur_neighbors[v], func_st_vert, func_fn_vert, func_is_used_vert);
        }

        func_fn_vert(index_vert);
    }
};