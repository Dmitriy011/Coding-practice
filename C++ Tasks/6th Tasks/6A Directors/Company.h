#pragma once

class Company
{
public:
    std::vector<Employee> employers;
    size_t n;

    explicit Company(size_t _n)
    {
        n = _n;
        employers.resize(_n);

        for (size_t i_employee = 0; i_employee < n; ++i_employee)
            employers[i_employee] = Employee(i_employee);
    }

    int Get_director_for_employee(int index_employee)
    {
        if (employers[index_employee].i_parent == index_employee)
            return index_employee;

        int director = Get_director_for_employee(
            employers[index_employee].i_parent);

        employers[index_employee].i_parent = director;

        return director;
    }
};