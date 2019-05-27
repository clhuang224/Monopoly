#ifndef GAME_H
#define GAME_H
#include "Block.h"
#include "Player.h"
#include "Start.h"
#include "House.h"
#include "Chance.h"
#include "Fortune.h"
#include "Map.h"
#include <ctime>
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <sstream>
using namespace std;
class Game
{
public:
	Game(string loadMapFile);
	~Game();

	//丟骰子
	size_t rollTheDice(size_t amount);
	//所有的印出
	void printUI();
private:
	int playerAmount = 0;//玩家數量
	int remainingRound = 0;
	vector<Player> players;
	size_t run = 0;
	Map map;//遊戲地圖
	Player bank;//defult宣告直接等於銀行
};

#endif