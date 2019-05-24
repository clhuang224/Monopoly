#include "Chance.h"

Chance::Chance(unsigned newPosition)
    : Block(newPosition, "機會", -2, {"    █    ",
                                      "    █    ",
                                      "    █    ",
                                      "    ▅    "})
{
    srand(time(NULL));
}

string Chance::getChance(Player agent)
{
    switch ((rand() % 2))
    {
    case 0:
        agent.stop(1);
        return "吃飯沒洗手，生病，休息一回合";
    case 1:
        agent.setMoney(agent.getMoney() + 100);
        return "逛街超爽的撿到一百元";
    case 2:
        agent.setMoney(agent.getMoney() - 300);
        return "觀光旅遊花費三百元";
    }
}