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

 void Block::setOutput(char player1 = ' ', char player2 = ' ', char player3 = ' ', char player4 = ' ')
 {
	 name = center(name, 10);
	 output = "____________"
			 "|          |"
			 "|" + sign[0] + "|"
			 "|" + sign[1] + "|"
			 "|" + sign[2] + "|"
			 "|" + sign[3] + "|"
			 "|" + name + "|"
			 "| " + player1 + "|" + player2 + "|" + player3 + "|" + player4 + "  |"
			 "|__________|";
 }

 string Block::center(const string s, const int w)
 {
	 stringstream ss, spaces;
	 int pad = w - s.size();
	 for (int i = 0; i < pad / 2; ++i)
	 {
		 spaces << " ";
	 }
	 ss << spaces.str() << s << spaces.str();
	 if (pad > 0 && pad % 2 != 0)
	 {
		 ss << " ";
	 }
	 return ss.str();
 }

 string Block::getOutput()
 {
	 return output;
 }