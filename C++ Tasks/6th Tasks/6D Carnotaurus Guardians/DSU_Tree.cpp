#include "DSU_Tree.h"


void DSU_tree::Add(int el)
{
    parent_vec[++count_elements_was_added] = el;
    DP[count_elements_was_added][0] = el;
    depth_vec[count_elements_was_added] = depth_vec[el] + 1;
    transitive[el].push_back(count_elements_was_added);

    for (int i = 1; i < ceil(log2(MAX_SIZE)); ++i)
        DP[count_elements_was_added][i] = DP[DP[count_elements_was_added][i - 1]][i - 1];
}

void DSU_tree::Delete(int elem_to_delete)
{
    tree.is_broke_tree_vec[elem_to_delete] = true;
    tree.transitive_vec[elem_to_delete] = tree.transitive_vec[parent_vec[elem_to_delete]];

    if (tree.is_broke_tree_vec[parent_vec[elem_to_delete]])
        tree.Union_2set(elem_to_delete, parent_vec[elem_to_delete]);

    for (size_t i = 0; i < transitive[elem_to_delete].size(); ++i)
    {
        if (tree.is_broke_tree_vec[transitive[elem_to_delete][i]])
            tree.Union_2set(transitive[elem_to_delete][i], elem_to_delete);
    }
}

int DSU_tree::Calculate_less_general_parent(int el_1st, int el_2st)
{

    if (depth_vec[el_1st] > depth_vec[el_2st])
        std::swap(el_1st, el_2st);

    for (int i = ceil(log2(MAX_SIZE)) - 1; i >= 0; --i)
    {
        if (depth_vec[el_2st] - depth_vec[el_1st] >= pow2_vec[i])
            el_2st = DP[el_2st][i];
    }

    if (el_1st == el_2st)
        return el_1st;

    for (int i_lvl_tree = ceil(log2(MAX_SIZE)) - 1; i_lvl_tree >= 0; --i_lvl_tree)
    {
        if (DP[el_1st][i_lvl_tree] != DP[el_2st][i_lvl_tree])
        {
            el_1st = DP[el_1st][i_lvl_tree];
            el_2st = DP[el_2st][i_lvl_tree];
        }
    }

    return tree.transitive_vec[tree.Find_root_elem_x(parent_vec[el_1st])];
}



