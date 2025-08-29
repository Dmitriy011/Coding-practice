#pragma once

#include <vector>

extern std::vector<int> depth_vec;

struct Independent_union_set_tree
{
    std::vector<int> parent_vec;
    std::vector<int> rang_vec;
    std::vector<int> transitive_vec;
    std::vector<bool> is_broke_tree_vec;

    explicit Independent_union_set_tree(int size_tree);

    void Union_2set(int elem_1st_set, int elem_2st_set);

    int Find_root_elem_x(int i);
};

