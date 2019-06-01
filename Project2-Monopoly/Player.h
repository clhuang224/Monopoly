#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <string>
#include "Stock.h"
#include "House.h"

using namespace std;

class Player
{
private:
	string name;
	unsigned int currentPosition;
	int cash;
	int deposit;
	vector<struct stockData> ownStock;
	vector<House*> ownHouse;
	int state = 0;
	int stopRound = 0;
	int color = 7;

public:
	~Player();
	Player();
	Player(const Player&);
	Player(string setName, unsigned int setPosition, int setCash, int setDeposit);

	void operator=(Player);

	string getName();
	void setName(string);

	void stop(int i);

	void setPosition(unsigned int pos);
	unsigned int getPosition();
	
	int getCash();
	void setCash(int number);
	void minusCash(int number);
	void plusCash(int number);

	int getDeposit();
	void setDeposit(int number);
	void minusDeposit(int number);
	void plusDeposit(int number);


	vector<struct stockData> getOwnStock();
	void buyStock(struct stockData buy);
	void sellStock(int sell,int newValue);

	int getColor();
	void setColor(int co);

	vector<House*> getOwnHouse();
	void setOwnHouse(House*);
	void freeHouse(House* free);
	void buyHouse(House* buy);
	void sellHouse(House* sell);

};

#endif