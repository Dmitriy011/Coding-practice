
#include "VertexHash.h"

VertexHash::VertexHash()
{
    len = 1;
    hash_v = 0;
}

VertexHash::VertexHash(int _len, int64_t _hash)
{
    len = _len;
    hash_v = _hash;
}