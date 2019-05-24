#include "House.h"

House::House(unsigned newPosition, string newName, unsigned newType, unsigned newLevel)
    : Block(newPosition, newName, newType)
{
    vector<string> sign;
    switch (newLevel)
    {
    case 0:
        sign = { "          ",
                 "  ���i��  ",
                 "    �i    ",
                 "          " };
        break;
    case 1:
        sign = { "    ��    ",
                 "  ���i��  ",
                 "    �i    ",
                 "          " };
        break;
    case 2:
        sign = { "   ����   ",
                 " ���i�i�� ",
                 "  �i�i�i  ",
                 "  �i�i�i  " };
        break;
    case 3:
        sign = { "  ���i��  ",
                 "���i�i�i��",
                 "  �i���i  ",
                 "  �i�i�i  " };
        break;
    }
    setSign(sign);
    level = newLevel;
    // priceList = �̾ڤ���X����
}

unsigned House::getLevel()
{
    return level;
}

void House::setLevel(unsigned newLevel)
{
    vector<string> newSign;
    switch (newLevel)
    {
    case 0:
        newSign = { "          ",
                    "  ���i��  ",
                    "    �i    ",
                    "          " };
        break;
    case 1:
        newSign = { "    ��    ",
                    "  ���i��  ",
                    "    �i    ",
                    "          " };
        break;
    case 2:
        newSign = { "   ����   ",
                    " ���i�i�� ",
                    "  �i�i�i  ",
                    "  �i�i�i  " };
        break;
    case 3:
        newSign = { "  ���i��  ",
                    "���i�i�i��",
                    "  �i���i  ",
                    "  �i�i�i  " };
        break;
    }
    setSign(newSign);
    level = newLevel;
}

unsigned House::getPrice()
{
    return priceList[level];
}