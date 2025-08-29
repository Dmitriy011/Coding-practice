#pragma once

#include <vector>
#include <map>

class Graph
{
public:
    std::vector<std::vector<int>> matrix_connectivity;
    std::map<std::pair<int, int>, int> cost_to_visit_edge;

    std::vector<bool> vert_used;
    std::vector<int> tmp_vec_search;
    std::vector<int> tmp_time_traversal;
    int cur_time_traversal;

    explicit Graph() {}

    explicit Graph(const int _size) { matrix_connectivity.resize(_size); }

    void AddEdge(const int vert_1st,  const int vert_2st, const int cost_this_edge);
};
