#pragma once

#include "Graph.h"

template <typename Type>
void DFS(int index_st_vert, int index_parent, Graph& G, Type func_process_vert)
{
    G.vert_used[index_st_vert] = true;
    G.tmp_vec_search[index_st_vert] = (G.cur_time_traversal)++;
    G.tmp_time_traversal[index_st_vert] = (G.tmp_vec_search)[index_st_vert];

    for (size_t i_vert_neighbour_to_st = 0; i_vert_neighbour_to_st < (G.matrix_connectivity[index_st_vert]).size(); ++i_vert_neighbour_to_st)
    {
        int index_next_vert = (G.matrix_connectivity[index_st_vert])[i_vert_neighbour_to_st];

        if (index_next_vert == index_parent)
            continue;

        if (G.vert_used[index_next_vert])
        {
            int tmp_a_val = G.tmp_vec_search[index_st_vert];
            int tmp_b_val = G.tmp_time_traversal[index_next_vert];
            G.tmp_vec_search[index_st_vert] = std::min(tmp_a_val, tmp_b_val);
        }
        else
        {
            DFS(index_next_vert, index_st_vert, G, func_process_vert);

            int tmp_a_val = G.tmp_vec_search[index_st_vert];
            int tmp_b_val = G.tmp_vec_search[index_next_vert];
            G.tmp_vec_search[index_st_vert] = std::min(tmp_a_val, tmp_b_val);

            if (G.tmp_vec_search[index_next_vert] > G.tmp_time_traversal[index_st_vert])
            {
                auto it = G.cost_to_visit_edge.find(std::make_pair (index_st_vert, index_next_vert));

                int tmp_cost = it->second;

                func_process_vert(tmp_cost);
            }
        }
    }
}