#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <utility>
#include <limits>

#include "Independent_union_set_tree.h"
#include "DSU_Tree.h"

const int MAX_SIZE = 200000;

std::vector<int> depth_vec;

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(nullptr);
    int res = 0;
    depth_vec.resize(MAX_SIZE);

    int m;
    std::cin >> m;

    std::vector<std::pair<char, std::vector<int>>> requests(m);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    for (int i = 0; i < m; ++i)
    {
        std::cin >> requests[i].first;

        int tmp1_val = 0;
        int tmp2_val = 0;
        if (requests[i].first == '+' || requests[i].first == '-')
        {
            std::cin >> tmp1_val;

            requests[i].second.push_back(tmp1_val);
        }
        else
        {
            std::cin >> tmp1_val >> tmp2_val;
            requests[i].second.push_back(tmp1_val);
            requests[i].second.push_back(tmp2_val);
        }
    }

    DSU_tree tree;

    for (int No_request = 0; No_request < m; ++No_request)
    {
        if (requests[No_request].first == '+')
            tree.Add(requests[No_request].second[0] - 1);
        else
        {
            if (requests[No_request].first == '-')
                tree.Delete(requests[No_request].second[0] - 1);
            else
            {
                res = tree.Calculate_less_general_parent(requests[No_request].second[0] - 1, requests[No_request].second[1] - 1) + 1;

                std::cout << res << '\n';
            }
        }
    }

    return 0;
}
