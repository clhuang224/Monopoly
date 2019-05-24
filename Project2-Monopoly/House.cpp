#include "House.h"

const vector<vector<string>> signList = { { "          ",
                                            "  ⅷⅸ  ",
                                            "        ",
                                            "          " } ,
                                          { "    《    ",
                                            "  ⅷⅸ  ",
                                            "        ",
                                            "          " } ,
                                          { "    《    ",
                                            "  ⅷⅸ  ",
                                            "        ",
                                            "          " } ,
                                          { "  ⅷⅸ  ",
                                            "ⅷⅸ",
                                            "  」  ",
                                            "    " } };

// Intent: ﹍て
// Pre: 竚嘿摸单基
// Post: ﹍てЧΘ
House::House(unsigned newPosition, string newName, int newType, unsigned newLevel, vector<unsigned> newPriceList)
    : Block(newPosition, newName, newType, signList[newLevel])
{
    level = newLevel;
    priceList = newPriceList;
}

// Intent: 眔┬单
// Pre: ┬ン
// Post: 肚level
unsigned House::getLevel()
{
    return level;
}

// Intent: 砞﹚┬单
// Pre: 穝单
// Post: level砆э跑
void House::setLevel(unsigned newLevel)
{
    level = newLevel;
    setSign(signList[newLevel]);
}

// Intent: 眔┬基窥
// Pre: ┬ン
// Post: 肚priceList[level]
unsigned House::getPrice()
{
    return priceList[level];
}