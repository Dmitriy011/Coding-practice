#pragma once

#include <set>

#include "Path.h"

std::vector<int32_t> GetNeighbour_vec(int32_t lenght_code, int32_t i_row, int32_t i_column, const std::vector<std::vector<bool>>& row_string, bool isStraight);

class Graph
{
public:
    Graph(const int32_t rows, const int32_t columns, std::vector<std::vector<bool>>& strings_ptr)
    {
        N_lenght_row = rows;
        M_lenght_column = columns;
        count_vert = rows * columns * 2 * 4;
        strings_row_vec = strings_ptr;
    }

    explicit Graph(int32_t vertex_count) : count_vert(vertex_count) {}

    Path Get_BFS_path(const std::set<int32_t>& vertexes);

private:
    int32_t count_vert;
    int32_t N_lenght_row = 0, M_lenght_column = 0;
    std::vector<std::vector<bool>> strings_row_vec;
};