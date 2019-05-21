#pragma once
#include "Block.h"
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Map
{
public:
	Map();
	Map(vector<Block> mapContent);
	~Map();
	void updateMap();
	int getMapSize();
private:
	vector<Block> map;
	int mapSize;
};