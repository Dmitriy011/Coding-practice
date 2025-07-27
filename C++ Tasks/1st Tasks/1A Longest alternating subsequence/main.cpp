#include <iostream>
#include <string>
#include <stack>

int main()
{
    // -- Считывание условия задачи --//
    std::string arr_strBreaks;                                          // Входная строка скобок
    std::cin >> arr_strBreaks;

    // -- Решение--//

    size_t res = 0;                                                     // счетчик обработанных корректных скобок
    std::stack<char> arr_openBreaks;                                    // Стек для хранения открывающих скобок
    for (size_t i = 0; i < arr_strBreaks.size(); ++i)                   // Цикл по строке 
    {
        if (arr_strBreaks[i] == '(' ||                                  // Если скобка открывающая: 1) Кладем в стек 2) Увеличиваем res
            arr_strBreaks[i] == '[' ||
            arr_strBreaks[i] == '{')
        {
            arr_openBreaks.push(arr_strBreaks[i]);
            ++res;
        }
        else                                                                 // Если скобка закрывающая:
        {                                                                    // В каждом блоке проверем 1) Совпадает ли закрывающая с вершиной стека
            if (arr_strBreaks[i] == ')')                                     // 1) Да - убираем вершину (т.е. закрыли пару) и увеличиваем res
            {                                                                // 1) Нет - ошибка: выводим res и завершаем
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

    if (arr_openBreaks.size() == 0)
        std::cout << "CORRECT";
    else
        std::cout << res;
}
