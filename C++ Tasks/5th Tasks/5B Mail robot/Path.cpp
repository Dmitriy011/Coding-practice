#include "Path.h"
#include "Graph.h"

Path::Path(const std::set<int32_t> _verts, std::vector<int32_t>&& distances)
{
    vert_set = _verts;
    distance_vec = distances;
}

std::vector<int32_t> Path::GetPath(int32_t fn_vert)
{
    std::vector<int32_t> path;
    path.push_back(fn_vert);

    while (!vert_set.count(path.back()))
    {
        int32_t v = path.back();
        std::vector<int32_t> vertex_neighbours = GetNeighbour_vec(v, N_lenght_row, M_lenght_column, string_row_vec, false);

        for (size_t i_vert_neighbour = 0; i_vert_neighbour < vertex_neighbours.size(); ++i_vert_neighbour)
        {
            if (distance_vec[vertex_neighbours[i_vert_neighbour]] + 1 == distance_vec[v])
            {
                path.push_back(vertex_neighbours[i_vert_neighbour]);
                break;
            }
        }
    }

    return path;
}
