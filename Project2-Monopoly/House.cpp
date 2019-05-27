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
House::House(unsigned newPosition, string newName, Player& newOwner, unsigned newLevel, unsigned cost, vector<unsigned> newPriceList, vector<unsigned> newPasserby)
	:Block(newPosition, newName, 1, signList[newLevel], newPasserby)
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

void House::setOwner(Player& p)
{
	owner = p;
}

// Intent: ���o�Фl����
// Pre: �Фl����
// Post: �^��priceList[level]
unsigned House::getPrice()
{
    return tollsList[level];
}