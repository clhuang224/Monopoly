#include "Block.h"

// Intent: 初始化
// Pre: 位置、名稱、類型、等級、標誌
// Post: 初始化完成
Block::Block(unsigned newPosition, string newName, int newType, vector<string> newSign, vector<unsigned> newPasserby)
{
    position = newPosition;
    name = newName;
    type = newType;
    sign = newSign;
    passerby = newPasserby;
}

// Intent: 取得類型
// Pre: 格子物件及繼承格子的物件
// Post: 回傳type
int Block::getType()
{
    return type;
}

// Intent: 取得名稱
// Pre: 格子物件及繼承格子的物件
// Post: 回傳name
string Block::getName()
{
    return name;
}

// Intent: 取得標誌
// Pre: 格子物件及繼承格子的物件
// Post: 回傳sign
vector<string> Block::getSign()
{
    return sign;
}

// Intent: 設定標誌
// Pre: 格子物件及繼承格子的物件
// Post: 回傳sign
 void Block::setSign(vector<string> newSign)
{
    sign = newSign;
}