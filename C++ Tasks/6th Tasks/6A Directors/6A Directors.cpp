#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <utility>
#include <limits>

#include "Employee.h"
#include "Company.h"

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t n = 0;
    size_t m = 0;
    std::cin >> n >> m;

    std::vector<int> res(m);

    std::vector<std::vector<int>> requests(m);

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    for (size_t i_req = 0; i_req < m; ++i_req)
    {
        std::string str_req;
        std::vector<int> tmp_elem_vec;
        int tmp_elem;

        std::getline(std::cin, str_req);
        std::istringstream input_str_stream(str_req);

        while (input_str_stream >> tmp_elem)
            tmp_elem_vec.push_back(tmp_elem);

        requests[i_req] = tmp_elem_vec;
    }

    Company company(n);

    for (size_t i_req = 0; i_req < requests.size(); ++i_req)
    {
        if (requests[i_req].size() == 1)
        {
            int index = requests[i_req][0] - 1;

            int director = company.Get_director_for_employee(index);

            res[i_req] = director + 1;
        }
        else
        {
            if (requests[i_req].size() == 2)
            {
                int a_parent_index = requests[i_req][0] - 1;
                int b_index = requests[i_req][1] - 1;

                if (company.Get_director_for_employee(b_index) == b_index && company.Get_director_for_employee(a_parent_index) != b_index)
                {
                    company.employers[b_index].i_parent = a_parent_index;
                    res[i_req] = 1;
                }
                else
                    res[i_req] = 0;
            }
        }
    }

    for (size_t i = 0; i < res.size(); ++i)
        std::cout << res[i] << '\n';

    return 0;
}
