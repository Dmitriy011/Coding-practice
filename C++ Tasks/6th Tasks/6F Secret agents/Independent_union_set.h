#pragma once

class Independent_union_set
{
public:
    std::vector<int> parent_vec;
    std::vector<int> rank_depth_set;

    explicit Independent_union_set(size_t _size);

    int Get_root_of_set(int index_vert);

    void Union_set(int a_elem_1st_set, int a_elem_2st_set);
};
