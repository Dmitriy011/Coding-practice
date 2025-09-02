#pragma once

struct Coin
{
//* pos Положение монеты
//* time Дедлайн в сек (время, до которого монету надо собрать)

    int32_t pos;   
    int32_t time;  

    //* Сортировка монет сначала по коорд, затем по дедлайну (если коорд совпадают).
    bool operator<(Coin rhs) const
    {
        return std::make_pair(pos, time) < std::make_pair(rhs.pos, rhs.time);
    }

    //* Сложение 2ух монет как векторов (используется в DP, где pos и time будут накапливаться как путь и время движ)
    Coin operator+(Coin rhs) const
    {
        return { pos + rhs.pos, time + rhs.time };
    }
};
