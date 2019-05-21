#pragma once
#include "Block.h"
#include <array>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Map
{
public:
	Map();
	Map(vector<Block> mapContent, array<int, 4> playerPositionsInput); //mapContent �s��ۦa�ϤW�Ҧ��� Block�FplayerPositionsInput �s��۩Ҧ����a����m
	~Map();
	void updateMap();
	void setCertainPlayerPosition(int playerID, int newPosition);
	int getCertainPlayerPosition(int playerID);
	int getMapSize();
private:
	vector<Block> map;
	array<int, 4> playerPositions;
	int mapSize;
};