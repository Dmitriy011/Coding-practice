#include <iostream>
#include <string>
#include <stack>

int main()
{
// ========= 1. Считывание задачи ========= //

//* arr_strBreaks: Входная строка скобок

    std::string arr_strBreaks;
    std::cin >> arr_strBreaks;

// ========= 2. Решение задачи ========= //

//* res: счетчик обработанных корректных скобок
//* std::stack<char> arr_openBreaks: Стек для хранения открывающих скобок
//**** 1) Цикл по строке 
//**** 2) Если скобка открывающая: 1. Кладем в стек 2. Увеличиваем res
//**** 3) Если скобка закрывающая: В каждом блоке проверем 1. Совпадает ли закрывающая с вершиной стека -> 1.1  Да - убираем вершину (т.е. закрыли пару) и увеличиваем res 1.2. Нет - ошибка: выводим res и завершаем

    size_t res = 0;
    std::stack<char> arr_openBreaks;
    // 1) 
    for (size_t i = 0; i < arr_strBreaks.size(); ++i)
    {
    // 2) 
        if (arr_strBreaks[i] == '(' || arr_strBreaks[i] == '[' ||  arr_strBreaks[i] == '{')
        {
            arr_openBreaks.push(arr_strBreaks[i]);
            ++res;
        }
        else
        {
    // 3)
            if (arr_strBreaks[i] == ')')
            {
                if (!arr_openBreaks.empty() && arr_openBreaks.top() == '(')
                {
                    arr_openBreaks.pop();
                    res++;
                }
                else
                {
                    std::cout << res;
                    return 0;
                }
            }
            else
            {
                if (arr_strBreaks[i] == ']')
                {
                    if (!arr_openBreaks.empty() && arr_openBreaks.top() == '[')
                    {
                        arr_openBreaks.pop();
                        ++res;
                    }
                    else
                    {
                        std::cout << res;
                        return 0;
                    }
                }
                else
                {
                    if (arr_strBreaks[i] == '}')
                    {
                        if (!arr_openBreaks.empty() && arr_openBreaks.top() == '{')
                        {
                            arr_openBreaks.pop();
                            ++res;
                        }
                        else
                        {
                            std::cout << res;
                            return 0;
                        }
                    }
                }
            }
        }
    }

// ========= 3. Вывод ответа ========= //
    if (arr_openBreaks.size() == 0)
        std::cout << "CORRECT";
    else
        std::cout << res;
}
