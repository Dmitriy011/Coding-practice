#include "Independent_union_set_tree.h"

Independent_union_set_tree::Independent_union_set_tree(int size_tree)
{
    rang_vec.resize(size_tree, 0);
    parent_vec.resize(size_tree);
    transitive_vec.resize(size_tree);
    is_broke_tree_vec.resize(size_tree);

    for (int i = 0; i < size_tree; ++i)
    {
        parent_vec[i] = i;
        transitive_vec[i] = i;
    }
}
void Independent_union_set_tree::Union_2set(int el_1st, int el_2st)
{
    int _x = el_1st;
    int _y = el_2st;
    el_1st = Find_root_elem_x(el_1st);
    el_2st = Find_root_elem_x(el_2st);

    int i_next = 0;
    if (depth_vec[_x] < depth_vec[_y])
        i_next = transitive_vec[el_1st];
    else
        i_next = transitive_vec[el_2st];

    if (el_1st == el_2st)
        return;

    if (rang_vec[el_1st] == rang_vec[el_2st])
        rang_vec[el_1st]++;

    if (rang_vec[el_1st] > rang_vec[el_2st])
    {
        parent_vec[el_2st] = el_1st;
        transitive_vec[el_1st] = i_next;
    }
    else
    {
        parent_vec[el_1st] = el_2st;
        transitive_vec[el_2st] = i_next;
    }
}

int Independent_union_set_tree::Find_root_elem_x(int i)
{
    if (i == parent_vec[i])
        return parent_vec[i];

    return Find_root_elem_x(parent_vec[i]);
}
