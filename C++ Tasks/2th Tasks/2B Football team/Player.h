#pragma once

struct Player
{
//* Ёффективность игрока
//* »ндекс игрока в исходном массиве
    int effectiveness;  
    size_t index;       
};

bool CompareEffectivenessPlayer(const Player& fitst_player, const Player& second_player)
{
    return fitst_player.effectiveness < second_player.effectiveness;
}

bool CompareIndexPlayer(const Player& fitst_player, const Player& second_player)
{
    return fitst_player.index < second_player.index;
}
