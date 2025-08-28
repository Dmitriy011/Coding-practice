#include <iostream>
#include <vector>

#include "BinaryIndexedTree.h"

BinaryIndexedTree::BinaryIndexedTree(int _len) : len(_len)
{
    prefix_freq.assign(len, 0);
}

int BinaryIndexedTree::GetStatistics(int k)
{
    if (Prefix_Si(len - 1) < k)
        return -2;

    int L = -1;
    int R = len - 1;

    while (R - L > 1)
    {
        int mid = (L + R) / 2;

        if (Prefix_Si(mid) < k)
            L = mid;
        else
            R = mid;
    }

    return R;
}

void BinaryIndexedTree::Inc(int i, int delta)
{
    for (; i < len; i = (i | (i + 1)))
        prefix_freq[i] += delta;
}

int BinaryIndexedTree::Prefix_Si(int i)
{
    int res = 0;

    for (; i >= 0; i = (i & (i + 1)) - 1)
        res += prefix_freq[i];

    return res;
}
