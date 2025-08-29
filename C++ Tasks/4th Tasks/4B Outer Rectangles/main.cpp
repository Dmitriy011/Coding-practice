#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <functional>
#include <utility>

#include "Segment.h"
#include "Event.h"
#include "RBTree.h"


bool Is_outer_rectangle(RBTree<>& _tree, Segment& _segment)
{
    auto node = _tree.root;
    auto compare = _tree.compare_;

    while (node)
    {
        if (node->key->bound_L < _segment.bound_L && _segment.bound_R < node->key->bound_R)
            break;

        if (compare(_segment, *node->key))
            node = node->L;
        else
            node = node->R;
    }

    if (!node)
        return true;

    return false;
}

int main()
{
// ========= 1. Считывание задачи ========= //
    size_t n;
    std::cin >> n;

    std::vector<Event> B_events_st_fn;
    B_events_st_fn.reserve(n * 2);

    for (size_t i_rectangle = 0; i_rectangle < n; ++i_rectangle)
    {
        int x1_L_down, y1_L_down, x2_R_up, y2_R_up;
        std::cin >> x1_L_down >> y1_L_down >> x2_R_up >> y2_R_up;

// ========= 2. Решение задачи ========= //
        if (x1_L_down > x2_R_up)
            std::swap(x1_L_down, x2_R_up);

        if (y1_L_down > y2_R_up)
            std::swap(y1_L_down, y2_R_up);

        Event event_1st = { {x1_L_down, x2_R_up}, y1_L_down, Event::TypeEvent::st_k };
        Event event_2st = { {x1_L_down, x2_R_up}, y2_R_up, Event::TypeEvent::fn_k };

        B_events_st_fn.push_back(event_1st);
        B_events_st_fn.push_back(event_2st);
    }

    auto func_compare = [](const Event& lhs, const Event& rhs)
    {
        return lhs.len < rhs.len;
    };

    std::sort(B_events_st_fn.begin(), B_events_st_fn.end(), func_compare);

    RBTree<> Tree;
    size_t count_outer_rectangle = 0;

    for (size_t i_event = 0; i_event < B_events_st_fn.size(); ++i_event)
    {
        if (B_events_st_fn[i_event].type == Event::TypeEvent::fn_k)
        {
            auto it = Tree.Find(B_events_st_fn[i_event].segment);
            if (!(it == Tree.Get_end_it()))
                Tree.DeleteNode(it);
        }
        else
        {
            if (Is_outer_rectangle(Tree, B_events_st_fn[i_event].segment))
            {
                Tree.Insert(B_events_st_fn[i_event].segment);
                ++count_outer_rectangle;
            }
        }
    }

// ========= 3. Вывод ответа ========= //
    std::cout << count_outer_rectangle << '\n';

    return 0;
}
