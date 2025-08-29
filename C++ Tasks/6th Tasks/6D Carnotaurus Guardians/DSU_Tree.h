#pragma once

#include <vector>

#include "Independent_union_set_tree.h"


extern std::vector<int> depth_vec;
extern const int MAX_SIZE;

class DSU_tree
{
public:
    std::vector<int> parent_vec;
    std::vector<std::vector<int>> transitive;
    std::vector<std::vector<int>> DP;
    std::vector<int>pow2_vec;

    int count_elements_was_added;

    Independent_union_set_tree tree;

    DSU_tree() : tree(MAX_SIZE)
    {
        parent_vec.resize(MAX_SIZE);
        transitive.resize(MAX_SIZE);
        DP.resize(MAX_SIZE, std::vector<int>(ceil(log2(MAX_SIZE)) + 1));
        pow2_vec.resize(ceil(log2(MAX_SIZE)) + 1);

        count_elements_was_added = 0;

        pow2_vec[0] = 1;
        for (int i = 1; i < ceil(log2(MAX_SIZE)) + 1; ++i)
            pow2_vec[i] = pow2_vec[i - 1] * 2;
    }

    void Add(int elem_to_add);

    void Delete(int elem_to_delete);

    int Calculate_less_general_parent(int el_1st,
        int el_2st);
};
