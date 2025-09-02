#include <iostream>
#include <vector>
#include <algorithm>

#include "Player.h"
#include "QuickSort.h"

//* n - количество игроков

// Находит макс. эф. команду, удовлетв условию сплочённости.
int64_t FindTeamRes(const std::vector <Player>& players, std::vector <Player>* team_res)
{
//**** 1) Отсорт игроков по эф (возрастающе): O(n log n)
//**** 2) Обработка случая одного игрока

//* R_index_player Правый конец окна (новый игрок в команд
//* L_worst_player_index Левый конец окна
//* tmp_sum_effectiveness Сумма эффективности текущего окна.
//* res_sum_effectiveness Макс. среди всех окон.

//**** 3) Берем сумму двух самых слабых игроков из окна (если след игрок (R_index_player) сильнее этой суммы, он "портит" сплочённость, убираем кого-то из начала окна)
//**** 4) Если можно вкл игрока: доб в команду
//**** 5) Если это послед игрок — сохр ответ
//**** 6) Если сумма текущ команды tmp_sum_effectiveness лучше предыдущ рез-та
//**** 7) Сохраняем гр окна (st_player_index, fn_player_index), чтобы потом восстановить команду.
//**** 8) Очищаем team_res (массив результата) и копир игроков из найденного окна [first_player_index, last_player_index] в team_res.
//**** 9) Сорт по индексам игроков
//**** 10) Завершаем, т.к.рассмотрели послед игрока
//**** 11) Если усл нарушено: искл самого слабого из окна(сдвигаем окно вправо).

    std::vector <Player> players_vec = players;

    // 1) 
    QuickSort(players_vec.begin(), players_vec.end(), CompareEffectivenessPlayer);

    // 2)
    if (players_vec.size() == 1)
    {
        team_res->resize(1);
        (*team_res)[0].effectiveness = players_vec[0].index;
        (*team_res)[0] = players_vec[0];

        return players_vec[0].effectiveness;
    }

    size_t R_index_player = 0;
    int L_worst_player_index = 0;
    int st_player_index = 0, fn_player_index = 0;
    int64_t tmp_sum_effectiveness = 0, res_sum_effectiveness = 0;
    while (R_index_player < players_vec.size())
    {
        // 3) 
        int64_t max_possible_efficiency = static_cast<int64_t>(players_vec[L_worst_player_index].effectiveness) + static_cast<int64_t>(players_vec[L_worst_player_index + 1].effectiveness);
        
        // 4) 
        if (players_vec[R_index_player].effectiveness <= max_possible_efficiency)
        {
            tmp_sum_effectiveness += players_vec[R_index_player].effectiveness;

        // 5) 
            if (R_index_player + 1 == players_vec.size())
            {
        // 6) 
                if (tmp_sum_effectiveness > res_sum_effectiveness)
                {
                    res_sum_effectiveness = tmp_sum_effectiveness;

        // 7)
                    st_player_index = L_worst_player_index;
                    fn_player_index = R_index_player;
                }

        // 8) 
                team_res->clear();
                for (int i_player = st_player_index;  i_player <= fn_player_index; ++i_player)
                {
                    team_res->push_back(players_vec[i_player]);
                }

        // 9) 
                QuickSort(team_res->begin(), team_res->end(), CompareIndexPlayer);

        // 10) 
                return res_sum_effectiveness;
            }

            ++R_index_player;
        }
        else 
        {
        // 11) 
            if (tmp_sum_effectiveness > res_sum_effectiveness)
            {
                res_sum_effectiveness = tmp_sum_effectiveness;

                st_player_index = L_worst_player_index;
                fn_player_index = R_index_player - 1;
            }

            tmp_sum_effectiveness = tmp_sum_effectiveness - players_vec[L_worst_player_index].effectiveness;
            ++L_worst_player_index;
        }
    }

    return 0;
}

int main()
{
// ========= 1. Считывание задачи ========= // 
    int n;
    std::cin >> n;

    std::vector <Player> team_res;
    std::vector <Player> efficiencyPlayers(n);
    for (int i = 0; i < n; ++i)
    {
        std::cin >> efficiencyPlayers[i].effectiveness;
        efficiencyPlayers[i].index = i;
    }

// ========= 2. Решение задачи ========= //
    std::cout << FindTeamRes(efficiencyPlayers, &team_res) << "\n";

// ========= 3. Вывод решения ========= // 
    for (size_t i = 0; i < team_res.size(); ++i)
        std::cout << team_res[i].index + 1 << " ";

    std::cout << "\n";

    return 0;
}
