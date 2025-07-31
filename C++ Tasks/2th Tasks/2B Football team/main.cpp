#include <iostream>
#include <vector>
#include <algorithm>

// n- количество игроков

struct Player
{
    int effectiveness;  // эффективность игрока
    size_t index;       // индекс игрока в исходном массиве
};

bool CompareEffectivenessPlayer(const Player& fitst_player, const Player& second_player)
{
    return fitst_player.effectiveness < second_player.effectiveness;
}

bool CompareIndexPlayer(const Player& fitst_player, const Player& second_player)
{
    return fitst_player.index < second_player.index;
}

void QuickSort(std::vector<Player>::iterator L,
    std::vector<Player>::iterator R,
    bool (*compare_player_is2st_more) (const Player&, const Player&))
{
    // Если отрезок пустой (L == R) или из одного эл (L + 1 == R), сорт не нужно
    if ((L == R) || (L + 1 == R))
        return;

    // Случ выбирается эл в диап [L, R) как опорный, чтобы избежать вырождения в худш случай (O(n²)).
    Player pivot = *(L + rand() % (R - L));

    // L и R — это исх гр подмассива, который надо отсорт.
    // Эти гр нужно сохр неизм, чтобы исп их при рекурсивных вызовах QuickSort.
    std::vector<Player>::iterator L_it = L;
    std::vector<Player>::iterator R_it = R;

    while (L_it < R_it)
    {
        if (R_it != R)
            ++L_it;

        --R_it;

        while ((*compare_player_is2st_more)(pivot, *R_it) == true)
            --R_it;

        while ((*compare_player_is2st_more)(*L_it, pivot) == true)
            ++L_it;

        if (L_it < R_it)
            std::swap(*L_it, *R_it);
    }

    QuickSort(L, R_it + 1, (*compare_player_is2st_more));
    QuickSort(R_it + 1, R, (*compare_player_is2st_more));
}

// Находит макс. эф. команду, удовлетв условию сплочённости.
int64_t FindTeamRes(const std::vector <Player>& players, std::vector <Player>* team_res)
{
    std::vector <Player> players_vec = players;

    // Отсорт игроков по эф (возрастающе): O(n log n)
    QuickSort(players_vec.begin(), players_vec.end(), CompareEffectivenessPlayer);

    // Обработка одного игрока:
    if (players_vec.size() == 1)
    {
        team_res->resize(1);
        (*team_res)[0].effectiveness = players_vec[0].index;
        (*team_res)[0] = players_vec[0];

        return players_vec[0].effectiveness;
    }

    size_t R_index_player = 0;                                           // Правый конец окна (новый игрок в команду).
    int L_worst_player_index = 0;                                        // Левый конец окна
    int st_player_index = 0, fn_player_index = 0;                        // Сумма эффективности текущего окна.
    int64_t tmp_sum_effectiveness = 0, res_sum_effectiveness = 0;        // Макс. среди всех окон.
    while (R_index_player < players_vec.size())
    {
        // Берем сумму двух самых слабых игроков из окна
        // ** (если след игрок (R_index_player) сильнее этой суммы, он "портит" сплочённость, убираем кого-то из начала окна) **
        int64_t max_possible_efficiency =
            static_cast<int64_t>(players_vec[L_worst_player_index].effectiveness) +
            static_cast<int64_t>(players_vec[L_worst_player_index + 1].effectiveness);
        
        //  Если можно вкл игрока: доб в команду
        if (players_vec[R_index_player].effectiveness <= max_possible_efficiency)
        {
            tmp_sum_effectiveness += players_vec[R_index_player].effectiveness;

            // Если это послед игрок — сохр ответ:
            if (R_index_player + 1 == players_vec.size())
            {
                // Если сумма текущ команды tmp_sum_effectiveness лучше предыдущ рез-та
                if (tmp_sum_effectiveness > res_sum_effectiveness)
                {
                    res_sum_effectiveness = tmp_sum_effectiveness;

                    // Сохраняем гр окна (st_player_index, fn_player_index), чтобы потом восстановить команду.
                    st_player_index = L_worst_player_index;
                    fn_player_index = R_index_player;
                }

                // Очищаем team_res (массив результата).
                team_res->clear();
                // Копир игроков из найденного окна [first_player_index, last_player_index] в team_res.
                for (int i_player = st_player_index;
                    i_player <= fn_player_index;
                    ++i_player)
                {
                    team_res->push_back(players_vec[i_player]);
                }

                // Сорт по индексам игроков
                QuickSort(team_res->begin(), team_res->end(), CompareIndexPlayer);

                // Завершаем, т.к. рассмотрели послед игрока
                return res_sum_effectiveness;
            }

            ++R_index_player;
        }
        else 
        {
            // Если усл нарушено: искл самого слабого из окна (сдвигаем окно вправо).
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
// -- Считывание задачи --// 
    int n;
    std::cin >> n;

    std::vector <Player> team_res;
    std::vector <Player> efficiencyPlayers(n);
    for (int i = 0; i < n; ++i)
    {
        std::cin >> efficiencyPlayers[i].effectiveness;
        efficiencyPlayers[i].index = i;
    }

    
// -- Решение задачи --// 
    std::cout << FindTeamRes(efficiencyPlayers, &team_res) << "\n";

    for (size_t i = 0; i < team_res.size(); ++i)
        std::cout << team_res[i].index + 1 << " ";

    std::cout << "\n";

    return 0;
}
