#ifndef GAME_H
#define GAME_H
#include "Map.h"
#include "Block.h"
#include "Player.h"
#include "Start.h"
#include "House.h"
#include "Chance.h"
#include "Fortune.h"
#include "Option.h"
#include <direct.h>
#include <ctime>
#include <string>
#include <vector>
#include <cstdlib>
#include <conio.h>
#include <fstream>
#include <sstream>
using namespace std;
class Game
{
public:
	Game(string loadMapFile);
	~Game();
	friend class Option;

	void save(string);
	void load();

	void runGame();
	void printUI();
	vector<Player> getPlayers();
	size_t rollTheDice();
private:
	int playerAmount = 0;//玩家數量
	int remainingRound = 0;//剩餘回合數
	bool is_FinishRound = false;//某個玩家的回合是否要結束
	vector<Player> players;
	int run = 0;//現在是誰的回合
	Map map;//遊戲地圖
	Player bank;//defult宣告直接等於銀行
};

#endif