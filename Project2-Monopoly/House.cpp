#include "House.h"

const vector<vector<string>> signList = { { "          ",
                                            "          ",
                                            "  ���i��  ",
                                            "    �i    " } ,
                                          { "          ",
                                            "    ��    ",
                                            "  ���i��  ",
                                            "    �i    " } ,
                                          { "   ����   ",
                                            " ���i�i�� ",
                                            "   �i�i   ",
                                            "   �i�i   " } ,
                                          { "  �i�i�i  ",
                                            "���i�i�i��",
                                            "  �i���i  ",
                                            "  �i�i�i  " } };

// Intent: ��l�ơ]�лx�|�ѵ��ŨM�w�^
// Pre: ��m�B�W�١B�����B���šB����C��
// Post: ��l�Ƨ���
House::House(unsigned newPosition, string newName, unsigned newLevel, unsigned cost = 0, vector<unsigned> newPriceList, vector<unsigned> newPasserby, int newOwner)
	: Block(newPosition, newName, 1, signList[newLevel], newPasserby)
{
	level = newLevel;
	cost_of_own = cost;//by���i
	tollsList = newPriceList;
	owner = newOwner;
}

// Intent: ���o�Фl����
// Pre: �Фl����
// Post: �^��level
unsigned House::getLevel()
{
    return level;
}

// Intent: �]�w�Фl���š]�лx�|�H���ŧ��ܡ^
// Pre: �s����
// Post: level�Msign�Q����
void House::setLevel(unsigned newLevel)
{
    level = newLevel;
    setSign(signList[newLevel]);
}

void House::setOwner(int playerID)
{
	owner = playerID;
}

// Intent: ���o�Фl����
// Pre: �Фl����
// Post: �^��priceList[level]
unsigned House::getPrice()
{
    return tollsList[level];
}