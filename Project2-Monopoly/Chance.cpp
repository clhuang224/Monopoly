#include "Chance.h"

Chance::Chance(unsigned newPosition)
    : Block(newPosition, "���|", -2, {"    �i    ",
                                      "    �i    ",
                                      "    �i    ",
                                      "    �f    "})
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
        return "�}��W�n���ߨ�@�ʤ�";
    case 1:
        changeMoney(agent, -300);
        return "�[���ȹC��O�T�ʤ�";
    }
}

namespace
{
    void changeMoney(Player agent, int amount)
    {
        agent.setMoney(agent.getMoney() + amount);
    }

}