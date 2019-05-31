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
	~Game();
	friend class Option;

	void save(string);
	void load(string);
	void clear();
	void printUI();
	void runGame();
	size_t rollTheDice();
	vector<Player> &getPlayers();
private:
	int playerAmount = 0;//���a�ƶq
	int remainingRound = 0;//�Ѿl�^�X��
	bool is_FinishRound = false;//�Y�Ӫ��a���^�X�O�_�n����
	bool restartFlag = false;
	int run = 0;//�{�b�O�֪��^�X
	string newGameName;
	Map map;//�C���a��
	Player bank;//defult�ŧi��������Ȧ�
	vector<Player> players;//���a(�U�hclass���������V��Vec������)
};

#endif