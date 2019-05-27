#include "Chance.h"

// Intent: ��l��
// Pre: ��m
// Post: ��l�Ƨ���
Chance::Chance(unsigned newPosition, vector<unsigned> newPasserby)
    : Block(newPosition, "���|", -2, { "  ���i��  ",
                                       "  �i�i�i  ",
                                       "  ���i��  ",
                                       "    �f    " }, newPasserby)
{
    srand(static_cast<unsigned>(time(NULL)));
}

// Intent: ����|
// Pre: ���a
// Post: �^�ǰT��
string Chance::getChance(Player agent)
{
    switch ((rand() % 3))
    {
    case 0:
        agent.stop(1);
        return "�Y���S�~��A�ͯf�A�𮧤@�^�X";
    case 1:
        agent.setCash(agent.getCash() + 100);
        return "�}��W�n���ߨ�@�ʤ�";
    case 2:
        agent.setCash(agent.getCash() - 300);
        return "�[���ȹC��O�T�ʤ�";
    }
}