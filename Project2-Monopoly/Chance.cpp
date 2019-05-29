#include "Chance.h"
#include "Player.h"

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

Chance::Chance(Chance& another)
    : Block(another.getPosition(), "���|", -2, { "  ���i��  ",
                                                 "  �i�i�i  ",
                                                 "  ���i��  ",
                                                 "    �f    " }, another.getPasserby())
{
}

Chance& Chance::operator=(Chance another)
{
    setPosition(another.getPosition());
    setName(another.getName());
    setType(another.getType());
    setSign(another.getSign());
    setPasserby(another.getPasserby());

    return (*this);
}

// Intent: ����|
// Pre: ���a
// Post: �^�ǰT��
string Chance::getChance(Player* agent)
{
    string message;
    switch ((rand() % 3))
    {
    case 0:
        agent->stop(1);
        message = "�Y���S�~��A�ͯf�A�𮧤@�^�X";
        break;
    case 1:
        agent->setCash(agent->getCash() + 100);
        message = "�}��W�n���ߨ�@�ʤ�";
        break;
    case 2:
        agent->setCash(agent->getCash() - 300);
        message = "�[���ȹC��O�T�ʤ�";
        break;
    }
    return message;
}