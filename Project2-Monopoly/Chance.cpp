#include "Chance.h"

// Intent: 初始化
// Pre: 位置
// Post: 初始化完成
Chance::Chance(unsigned newPosition, vector<unsigned> newPasserby)
    : Block(newPosition, "機會", -2, { "  ◢█◣  ",
                                       "  ███  ",
                                       "  ◥█◤  ",
                                       "    ▅    " }, newPasserby)
{
    srand(static_cast<unsigned>(time(NULL)));
}

// Intent: 抽機會
// Pre: 玩家
// Post: 回傳訊息
string Chance::getChance(Player agent)
{
    switch ((rand() % 3))
    {
    case 0:
        agent.stop(1);
        return "吃飯沒洗手，生病，休息一回合";
    case 1:
        agent.setCash(agent.getCash() + 100);
        return "逛街超爽的撿到一百元";
    case 2:
        agent.setCash(agent.getCash() - 300);
        return "觀光旅遊花費三百元";
    }
}