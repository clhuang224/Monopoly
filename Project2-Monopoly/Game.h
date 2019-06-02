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
	Game(string);
	friend class Option;

	void save(string);
	void load(string);
	void clear();
	void printUI();
	void runGame();
	size_t rollTheDice();
	vector<Player> &getPlayers();
    int getRun();
    Map* getMap();
private:
	int playerAmount = 0;//玩家數量
	int remains = 0;//剩餘玩家數量
	array<bool,4> lose = { false,false,false,false };//玩家的破產flag
	int remainingRound = 0;//剩餘回合數
	bool isFinishRound = false;//某個玩家的回合是否要結束
	bool restartFlag = false;//加載遊戲flag
	int run = 0;//現在是誰的回合
	string newGameName;//加載遊戲用的檔名暫存
	Map map;//遊戲地圖
	Player bank;//defult宣告直接等於銀行
	vector<Player> players;//玩家(下層class均直接指向此Vec的元素)
	void printPlayer();
};

#endif