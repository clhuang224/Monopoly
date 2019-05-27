#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// -2機會 -1命運 0起點 1房子 2銀行 3監獄 4醫院
enum { CHANCE = -2, FORTUNE = -1, START = 0, HOUSE = 1, BANK = 2, PRISON = 3, HOSPITAL = 4 };

class Block
{
public:
    Block(unsigned newPosition,
          string newName,
          int newType,
          vector<string> newSign = {},
          vector<unsigned> newPasserby = {});

    // 取得格子類型
    // -2機會 -1命運 0起點 1房子 2銀行 3監獄 4醫院
    // basemap.txt裡沒有2~4的格子 但如果要自製地圖就可以用
    int getType();

    // 取得格子標誌
    vector<string> getSign();

    // 設定格子標誌
    void setSign(vector<string> newSign);

    // 取得格子名稱
    string getName();

	//回傳整個格子
	string toString();

	////設定擁有者 House
	//virtual void setOwner() = 0;

	//// 取得當下價格 House
	//virtual unsigned getPrice() = 0;

	//// 設定等級 sign也會隨之改變 House
	//virtual void setLevel(unsigned newLevel) = 0;


private:
    unsigned position;
    string name; // 最長四個字
    int type;
    vector<string> sign; // 10x4
    vector<unsigned> passerby;

    /*
    格子格式：
     __________
    |          |
    |##########|
    |##########|
    |##########|
    |##########|
    |範 例 名 稱|
    |１|２|３|４|
    |__________|

    */

};

#endif // !BLOCK_H