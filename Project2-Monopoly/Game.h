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
#include <conio.h>
#include <fstream>
#include <sstream>
using namespace std;
class Game
{
public:
	Game(string loadMapFile);
	~Game();

	void printUI();
	void readKeyBoard();
	vector<Player> getPlayers();
	size_t rollTheDice();
private:
	int playerAmount = 0;//���a�ƶq
	int remainingRound = 0;
	vector<Player> players;
	size_t run = 0;
	Map map;//�C���a��
	Player bank;//defult�ŧi��������Ȧ�
};

#endif