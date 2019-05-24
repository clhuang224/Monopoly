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
    switch ((rand() % 2))
    {
    case 0:
        agent.stop(1);
        return "�Y���S�~��A�ͯf�A�𮧤@�^�X";
    case 1:
        agent.setMoney(agent.getMoney() + 100);
        return "�}��W�n���ߨ�@�ʤ�";
    case 2:
        agent.setMoney(agent.getMoney() - 300);
        return "�[���ȹC��O�T�ʤ�";
    }
}