#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <utility>

#include "Cell.h"
#include "Path.h"
#include "Graph.h"

const int32_t INF = static_cast<int32_t>(1e7);

inline int32_t Get_code_calculate(int32_t coord_row,  int32_t coord_column, char code_direction, char code_rotate, int32_t N_count_columns);

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    int32_t min_path = static_cast < int32_t>(1e6) + 1;
    std::vector<std::pair<int32_t, int32_t>> res;
    bool flag_res = true;

    int32_t N_rows = 0, M_columns = 0;
    int32_t st_index_row = 0, fn_index_row = 0;
    int32_t st_index_column = 0, fin_index_column = 0;

    std::cin >> N_rows >> M_columns;

    std::vector<std::vector<bool>> info_field(N_rows, std::vector<bool>(M_columns, true));

    for (int i_row = 0; i_row < N_rows; ++i_row)
    {
        std::string tmp_cur_row;
        std::cin >> tmp_cur_row;

        for (int i_elem_in_row = 0; i_elem_in_row < M_columns; ++i_elem_in_row)
        {
            if (tmp_cur_row[i_elem_in_row] == '#')
                info_field[i_row][i_elem_in_row] = false;
        }
    }

    std::cin >> st_index_row >> st_index_column;
    std::cin >> fn_index_row >> fin_index_column;
    --st_index_row;
    --st_index_column;
    --fn_index_row;
    --fin_index_column;

    Graph G(N_rows, M_columns, info_field);
    Path best_path;
    int32_t best_code_fn = Get_code_calculate(fn_index_row, fin_index_column, 'N', 'L', M_columns);
    std::set<int32_t> vertexes;

    std::set<int32_t> code_direction = { 'N', 'W', 'S', 'E' };
    std::set<int32_t> code_rotation = { 'R', 'L' };
    for (size_t i_code_direction = 0; i_code_direction < code_direction.size(); ++i_code_direction)
    {
        std::set<int32_t>::iterator it_direction_code = std::next(code_direction.begin(), i_code_direction);

        for (size_t i_code_rotate = 0; i_code_rotate < code_rotation.size(); ++i_code_rotate)
        {
            std::set<int32_t>::iterator it_rotation_code = std::next(code_rotation.begin(), i_code_rotate);

            int32_t current_start_code = Get_code_calculate(st_index_row, st_index_column, *it_direction_code, *it_rotation_code, M_columns);

            vertexes.insert(current_start_code);
        }
    }

    Path paths = G.Get_BFS_path(vertexes);

    for (size_t i_code_direction = 0; i_code_direction < code_direction.size(); ++i_code_direction)
    {
        std::set<int32_t>::iterator it_direction_code = std::next(code_direction.begin(), i_code_direction);

        for (size_t i_code_rotate = 0; i_code_rotate < code_rotation.size(); ++i_code_rotate)
        {
            std::set<int32_t>::iterator it_rotation_code = std::next(code_rotation.begin(), i_code_rotate);

            int32_t curr_finish_code = Get_code_calculate(fn_index_row, fin_index_column, *it_direction_code, *it_rotation_code,  M_columns);

            int32_t len_cur_cide = paths.distance_vec[curr_finish_code];
            if (len_cur_cide < min_path)
            {
                min_path = len_cur_cide;
                best_path = paths;
                best_code_fn = curr_finish_code;
            }
        }
    }

    if (min_path < static_cast < int32_t>(1e6) + 1)
    {
        std::vector<std::pair<int32_t, int32_t>> coord_cell_pair;

        std::vector<int32_t> best_codes = best_path.GetPath(best_code_fn);
        std::reverse(best_codes.begin(), best_codes.end());

        std::vector<std::pair<int32_t, int32_t>> best_coords;

        for (size_t i_code = 0; i_code < best_codes.size(); ++i_code)
        {
            int32_t size_code_string = best_codes[i_code] / 8;
            int32_t coord_row = size_code_string % M_columns;
            int32_t coord_column = size_code_string / M_columns;

            std::pair<int32_t, int32_t> coord_column_row = std::make_pair(coord_row, coord_column);

            best_coords.push_back(coord_column_row);
        }

        res = best_coords;
        flag_res = true;
    }
    else
        flag_res = false;

    if (!flag_res)
        std::cout << "-1\n";
    else
    {
        std::cout << res.size() - 1 << '\n';

        for (size_t i = 0; i < res.size(); ++i)
            std::cout << res[i].second + 1 << " " << res[i].first + 1 << '\n';
    }

    return 0;
}

inline int32_t Get_code_calculate(int32_t coord_row,  int32_t coord_column, char code_direction, char code_rotate, int32_t N_count_columns)
{
    std::map<char, int32_t> code_direction_map = { {'N', 0}, {'W', 1}, {'S', 2}, {'E', 3} };
    std::map<char, int32_t> code_rotation_map = { {'L', 0}, {'R', 1} };

    return code_rotation_map[code_rotate] + 2 * code_direction_map[code_direction] + 2 * 4 * coord_column + 2 * 4 * N_count_columns * coord_row;
}

Path Graph::Get_BFS_path(const std::set<int32_t>& vertexes)
{
    std::queue<int32_t> vert_not_processed;
    std::vector<int32_t> distance_vec(count_vert, INF);

    for (size_t v = 0; v < vertexes.size(); ++v)
    {
        std::set<int32_t>::iterator it = std::next(vertexes.begin(), v);

        vert_not_processed.push(*it);
        distance_vec[*it] = 0;
    }

    while (!vert_not_processed.empty())
    {
        int32_t cur_index_vert = vert_not_processed.front();
        vert_not_processed.pop();
        std::vector<int32_t> vert_neighbour_vec = GetNeighbour_vec(cur_index_vert, N_lenght_row, M_lenght_column, strings_row_vec, true);

        for (size_t i_vert_neighbour = 0; i_vert_neighbour < vert_neighbour_vec.size(); ++i_vert_neighbour)
        {
            if (distance_vec[vert_neighbour_vec[i_vert_neighbour]] == INF)
            {
                distance_vec[vert_neighbour_vec[i_vert_neighbour]] = distance_vec[cur_index_vert] + 1;

                vert_not_processed.push(vert_neighbour_vec[i_vert_neighbour]);
            }
        }
    }

    Path paths = Path(vertexes, std::move(distance_vec));
    paths.string_row_vec = strings_row_vec;
    paths.N_lenght_row = N_lenght_row;
    paths.M_lenght_column = M_lenght_column;

    return paths;
}
