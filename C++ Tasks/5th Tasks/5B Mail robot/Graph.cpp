#include "iostream"
#include "vector"

#include "Graph.h"
#include "MovementData.h"

std::vector<int32_t> GetNeighbour_vec(int32_t lenght_code, int32_t i_row, int32_t i_column, const std::vector<std::vector<bool>>& row_string, bool isStraight)
{
    int32_t len_code_rotate = lenght_code % 2;
    int32_t len_code_direction = (lenght_code / 2) % 4;

    int32_t coord_row = (lenght_code / 8) / i_column;
    int32_t coord_column = (lenght_code / 8) % i_column;

    const std::vector<std::pair<int8_t, int8_t>>& shift_possible = movements[len_code_direction][len_code_rotate];

    std::vector<int32_t> neighbour_vec;

    for (size_t i_possible_shift = 0; i_possible_shift < shift_possible.size(); ++i_possible_shift)
    {
        int32_t lenght_direction_code = shift_possible[i_possible_shift].first;
        int32_t lenght_rotation_code = shift_possible[i_possible_shift].second;
        std::pair<int32_t, int32_t> shift_pair;

        std::vector<std::pair<int8_t, int8_t>> tmp_shift_vec =
        {
            {-1, 0},
            {0, -1},
            {1, 0},
            {0, 1}
        };

        int32_t tmp_coord_row = coord_row;
        int32_t tmp_coord_column = coord_column;

        if (isStraight == true)
        {
            shift_pair = tmp_shift_vec[lenght_direction_code];

            tmp_coord_row = tmp_coord_row + shift_pair.first;
            tmp_coord_column = tmp_coord_column + shift_pair.second;
        }
        else
        {
            shift_pair = tmp_shift_vec[len_code_direction];

            tmp_coord_row = tmp_coord_row - shift_pair.first;
            tmp_coord_column = tmp_coord_column - shift_pair.second;
        }

        if ((tmp_coord_row >= 0 && tmp_coord_column >= 0 && tmp_coord_row < i_row && tmp_coord_column < i_column) && row_string[tmp_coord_row][tmp_coord_column])
        {
            neighbour_vec.push_back(lenght_rotation_code + 2 * lenght_direction_code + 2 * 4 * tmp_coord_column + 2 * 4 * i_column * tmp_coord_row);
        }
    }

    return neighbour_vec;
}
