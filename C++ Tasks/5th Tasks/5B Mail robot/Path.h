#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <set>

class Path
{
public:
    std::vector<int32_t> distance_vec;
    int32_t N_lenght_row = 0, M_lenght_column = 0;
    std::vector<std::vector<bool>> string_row_vec;

    Path() {}

    Path(const std::set<int32_t> _verts, std::vector<int32_t>&& distances);

    std::vector<int32_t> GetPath(int32_t fn_vert);

private:
    std::set<int32_t> vert_set;
};
