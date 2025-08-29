#pragma once

struct Cell
{
    int32_t coord_row_cur_cell;
    int32_t coord_column_cur_cell;

    char code_direction;
    char code_rotate;

    Cell() = default;
};
