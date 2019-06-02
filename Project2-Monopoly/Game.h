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
#include "Stock.h"
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
	Stock stock;
    int getRun();
    Map* getMap();
private:
	int playerAmount = 0;//���a�ƶq
	int remains = 0;//�Ѿl���a�ƶq
	array<bool,4> lose = { false,false,false,false };//���a���}��flag
	int remainingRound = 0;//�Ѿl�^�X��
	bool isFinishRound = false;//�Y�Ӫ��a���^�X�O�_�n����
	bool restartFlag = false;//�[���C��flag
	int run = 0;//�{�b�O�֪��^�X
	string newGameName;//�[���C���Ϊ��ɦW�Ȧs
	Map map;//�C���a��
	Player bank;//defult�ŧi��������Ȧ�
	vector<Player> players;//���a(�U�hclass���������V��Vec������)
	void printPlayer();
};

#endif