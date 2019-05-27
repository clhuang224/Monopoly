#pragma once
#include "Block.h"
#include <array>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>

using namespace std;

class Map
{
public:
	Map();
	Map(Map&);
	//mapContent 存放著地圖上所有的 Block；playerPositionsInput 存放著所有玩家的位置
	Map(vector<Block&> mapContent, array<int, 4> playerPositionsInput, string name);
	~Map();
	void updateMap();
	void setConsoleCursorPosition(int x, int y);
	COORD getConsoleCursorPosition();
	void setCertainPlayerPosition(int playerID, int newPosition);
	int getCertainPlayerPosition(int playerID);
	int getMapSize();
private:
	vector<Block&> map;
	array<int, 4> playerPositions;
	int mapSize;
	//我也不知道這要幹嘛，.txt有地圖名子 by昱展
	string mapName;
};