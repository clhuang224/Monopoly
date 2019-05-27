#include "House.h"

const vector<vector<string>> signList = { { "          ",
                                            "          ",
                                            "  ◢█◣  ",
                                            "    █    " } ,
                                          { "          ",
                                            "    ▲    ",
                                            "  ◢█◣  ",
                                            "    █    " } ,
                                          { "   ◢◣   ",
                                            " ◢██◣ ",
                                            "   ██   ",
                                            "   ██   " } ,
                                          { "  ███  ",
                                            "◢███◣",
                                            "  █★█  ",
                                            "  ███  " } };

// Intent: 初始化（標誌會由等級決定）
// Pre: 位置、名稱、類型、等級、價格列表
// Post: 初始化完成
House::House(unsigned newPosition, string newName, Player& newOwner, unsigned newLevel, unsigned cost, vector<unsigned> newPriceList, vector<unsigned> newPasserby)
	:Block(newPosition, newName, 1, signList[newLevel], newPasserby)
{
	level = newLevel;
	cost_of_own = cost;//by魚展
	tollsList = newPriceList;
	owner = newOwner;
}

// Intent: 取得房子等級
// Pre: 房子物件
// Post: 回傳level
unsigned House::getLevel()
{
    return level;
}

// Intent: 設定房子等級（標誌會隨等級改變）
// Pre: 新等級
// Post: level和sign被改變
void House::setLevel(unsigned newLevel)
{
    level = newLevel;
    setSign(signList[newLevel]);
}

void House::setOwner(Player& p)
{
	owner = p;
}

// Intent: 取得房子價錢
// Pre: 房子物件
// Post: 回傳priceList[level]
unsigned House::getPrice()
{
    return tollsList[level];
}