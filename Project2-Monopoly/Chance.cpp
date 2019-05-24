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
    string message;
    switch ((rand() % 2))
    {
    case 0:
        changeMoney(agent, 100);
        return "逛街超爽的撿到一百元";
    case 1:
        changeMoney(agent, -300);
        return "觀光旅遊花費三百元";
    }
}

namespace
{
    void changeMoney(Player agent, int amount)
    {
        agent.setMoney(agent.getMoney() + amount);
    }

}