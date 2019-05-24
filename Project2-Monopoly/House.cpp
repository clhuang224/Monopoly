#include "House.h"

House::House(unsigned newPosition, string newName, unsigned newType, unsigned newLevel)
    : Block(newPosition, newName, newType)
{
    vector<string> sign;
    switch (newLevel)
    {
    case 0:
        sign = { "          ",
                 "  ◢█◣  ",
                 "    █    ",
                 "          " };
        break;
    case 1:
        sign = { "    ▲    ",
                 "  ◢█◣  ",
                 "    █    ",
                 "          " };
        break;
    case 2:
        sign = { "   ◢◣   ",
                 " ◢██◣ ",
                 "  ███  ",
                 "  ███  " };
        break;
    case 3:
        sign = { "  ◢█◣  ",
                 "◢███◣",
                 "  █★█  ",
                 "  ███  " };
        break;
    }
    setSign(sign);
    level = newLevel;
    // priceList = 依據文件找出價錢
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
                    "  ◢█◣  ",
                    "    █    ",
                    "          " };
        break;
    case 1:
        newSign = { "    ▲    ",
                    "  ◢█◣  ",
                    "    █    ",
                    "          " };
        break;
    case 2:
        newSign = { "   ◢◣   ",
                    " ◢██◣ ",
                    "  ███  ",
                    "  ███  " };
        break;
    case 3:
        newSign = { "  ◢█◣  ",
                    "◢███◣",
                    "  █★█  ",
                    "  ███  " };
        break;
    }
    setSign(newSign);
    level = newLevel;
}

unsigned House::getPrice()
{
    return priceList[level];
}