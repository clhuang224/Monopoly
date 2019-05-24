#include "Fortune.h"

Fortune::Fortune(unsigned newPosition)
    : Block(newPosition, "�R�B", -1, { "  ���i��  ",
                                       "  �i  �i  ",
                                       "    ����  ",
                                       "    �f    " })
{
    srand(time(NULL));
}

string Fortune::getFortune(Player agent)
{
    switch ((rand() % 3))
    {
    case 0:
        agent.setPosition(agent.getPosition()-3);
        return "�J�W�g�۬y�A��h�T��";
    case 1:
        // �ϥΪ̥ιϧΤ������l������
        // agent.setPosition(newPosition);
        return "�J��j���a���A���ʦܷQ�n���a��";
    case 2:
        // agent.setPosition(randomPosition);
        return "���W�ɪŪ��A�H���ǰe";
    }
}