#include "Graph.h"

void Graph::AddEdge(const int v1, const int v2, const int cost)
{
    matrix_connectivity[v1].push_back(v2);
    matrix_connectivity[v2].push_back(v1);

    cost_to_visit_edge[std::make_pair(v1, v2)] = cost;
    cost_to_visit_edge[std::make_pair(v2, v1)] = cost;
}