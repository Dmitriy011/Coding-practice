#include "MovementData.h"

const std::map<std::string, std::vector<std::string>> code_movement_map =
{
    {"NL", {"NL", "WR", "SL"}},
    {"NR", {"NR", "EL", "SR"}},
    {"WL", {"WL", "SR", "EL"}},
    {"WR", {"WR", "NL", "ER"}},
    {"SL", {"SL", "ER", "NL"}},
    {"SR", {"SR", "WL", "NR"}},
    {"EL", {"EL", "NR", "WL"}},
    {"ER", {"ER", "SL", "WR"}}
};

const std::vector<std::vector<std::vector<std::pair<int8_t, int8_t>>>> movements =
{
    {
        {{0, 0}, {1, 1}, {2, 0}},
        {{0, 1}, {3, 0}, {2, 1}}
    },
    {
        {{1, 0}, {2, 1}, {3, 0}},
        {{1, 1}, {0, 0}, {3, 1}}
    },
    {
        {{2, 0}, {3, 1}, {0, 0}},
        {{2, 1}, {1, 0}, {0, 1}}
    },
    {
        {{3, 0}, {0, 1}, {1, 0}},
        {{3, 1}, {2, 0}, {1, 1}}
    }
};