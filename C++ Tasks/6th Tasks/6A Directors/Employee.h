#pragma once

struct Employee
{
    int i_employee;
    int i_parent;

    explicit Employee() {}

    explicit Employee(int _index)
    {
        i_employee = _index;
        i_parent = _index;
    }
};


