#include "Fortune.h"
#include "Player.h"

// Intent: ��l��
// Pre: ��m
// Post: ��l�Ƨ���
Fortune::Fortune(unsigned newPosition, vector<unsigned> newPasserby)
    : Block(newPosition, "�R�B", -1, { "  ���i��  ",
                                       "  �i  �i  ",
                                       "    ����  ",
                                       "    �f    " }, newPasserby)
{
    srand(static_cast<unsigned>(time(NULL)));
}

Fortune::Fortune(Fortune& another)
    : Block(another.getPosition(), "�R�B", -1, { "  ���i��  ",
                                                 "  �i  �i  ",
                                                 "    ����  ",
                                                 "    �f    " }, another.getPasserby())
{
}

Fortune& Fortune::operator=(Fortune another)
{
    setPosition(another.getPosition());
    setName(another.getName());
    setType(another.getType());
    setSign(another.getSign());
    setPasserby(another.getPasserby());

    return (*this);
}

// Intent: ��R�B
// Pre: ���a
// Post: �^�ǰT��
string Fortune::getFortune(Player* agent)
{
    string message;
    switch (rand() % 3)
    {
    case 0:
		/*���T�w�ݤ��ݭn�ɤW�h��T�B���ʶR�Ŧaor���L���O???�ثe�S��*/
        agent->setPosition(agent->getPosition()-3);
        message = "�J�W�g�۬y�A��h�T��";
        break;
    case 1:
        // �ϥΪ̥ιϧΤ������l������
        //agent->setPosition(newPosition);
        message = "�J��j���a���A���ʦܷQ�n���a��";
        break;
    case 2:
        //agent->setPosition(randomPosition);
        message = "���W�ɪŪ��A�H���ǰe";
        break;
    }
    return message;
}
