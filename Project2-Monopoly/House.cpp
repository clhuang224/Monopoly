#include "House.h"

const vector<vector<string>> signList = { { "          ",
                                            "  ���i��  ",
                                            "    �i    ",
                                            "          " } ,
                                          { "    ��    ",
                                            "  ���i��  ",
                                            "    �i    ",
                                            "          " } ,
                                          { "    ��    ",
                                            "  ���i��  ",
                                            "    �i    ",
                                            "          " } ,
                                          { "  ���i��  ",
                                            "���i�i�i��",
                                            "  �i���i  ",
                                            "  �i�i�i  " } };

// Intent: ��l��
// Pre: ��m�B�W�١B�����B���šB����C��
// Post: ��l�Ƨ���
House::House(unsigned newPosition, string newName, int newType, unsigned newLevel, vector<unsigned> newPriceList)
    : Block(newPosition, newName, newType, signList[newLevel])
{
    level = newLevel;
    priceList = newPriceList;
}

// Intent: ���o�Фl����
// Pre: �Фl����
// Post: �^��level
unsigned House::getLevel()
{
    return level;
}

// Intent: �]�w�Фl����
// Pre: �s����
// Post: level�Q����
void House::setLevel(unsigned newLevel)
{
    level = newLevel;
    setSign(signList[newLevel]);
}

// Intent: ���o�Фl����
// Pre: �Фl����
// Post: �^��priceList[level]
unsigned House::getPrice()
{
    return priceList[level];
}