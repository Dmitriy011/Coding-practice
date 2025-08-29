#pragma once

struct Event
{
    enum class TypeEvent { st_k, fn_k };

    Segment segment;
    int len;
    TypeEvent type;
};
