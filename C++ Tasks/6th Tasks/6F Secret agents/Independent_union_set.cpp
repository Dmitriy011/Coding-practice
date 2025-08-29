#include <vector>

#include "Independent_union_set.h"

Independent_union_set::Independent_union_set(size_t _size)
{
    parent_vec.resize(_size);
    rank_depth_set.resize(_size);

    for (size_t i = 0; i < _size; ++i)
    {
        parent_vec[i] = i;
        rank_depth_set[i] = 0;
    }
}

int Independent_union_set::Get_root_of_set(int i)
{
    if (i == parent_vec[i])
        return i;

    int parent_value = parent_vec[i];
    int root_value = Get_root_of_set(parent_value);
    parent_vec[i] = root_value;

    return root_value;
}

void Independent_union_set::Union_set(int el_1st, int el_2st)
{
    el_1st = Get_root_of_set(el_1st);
    el_2st = Get_root_of_set(el_2st);

    if (el_1st != el_2st)
    {
        if (rank_depth_set[el_1st] < rank_depth_set[el_2st])
            std::swap(el_1st, el_2st);

        parent_vec[el_2st] = el_1st;

        if (rank_depth_set[el_1st] == rank_depth_set[el_2st])
            ++rank_depth_set[el_1st];
    }
}


