#include "Block.h"

// Intent: ��l��
// Pre: ��m�B�W�١B�����B���šB�лx
// Post: ��l�Ƨ���
Block::Block(unsigned newPosition, string newName, int newType, vector<string> newSign, vector<unsigned> newPasserby)
{
    position = newPosition;
    name = newName;
    type = newType;
    sign = newSign;
    passerby = newPasserby;
}

// Intent: ���o����
// Pre: ��l������~�Ӯ�l������
// Post: �^��type
int Block::getType()
{
    return type;
}

// Intent: ���o�W��
// Pre: ��l������~�Ӯ�l������
// Post: �^��name
string Block::getName()
{
    return name;
}

// Intent: ���o�лx
// Pre: ��l������~�Ӯ�l������
// Post: �^��sign
vector<string> Block::getSign()
{
    return sign;
}

// Intent: �]�w�лx
// Pre: ��l������~�Ӯ�l������
// Post: �^��sign
 void Block::setSign(vector<string> newSign)
{
    sign = newSign;
}