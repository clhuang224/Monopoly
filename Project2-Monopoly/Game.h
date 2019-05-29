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
	int playerAmount = 0;//���a�ƶq
	int remainingRound = 0;//�Ѿl�^�X��
	bool is_FinishRound = false;//�Y�Ӫ��a���^�X�O�_�n����
	vector<Player> players;
	int run = 0;//�{�b�O�֪��^�X
	Map map;//�C���a��
	Player bank;//defult�ŧi��������Ȧ�
};

#endif