#pragma once
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
	vector<House&> ownHouse;
	int state = 0;
	int stopRound = 0;

public:
	~Player();
	Player(string setName, unsigned int setPosition, int setCash);

	void printPlayer();
	void stop(int i);

	void setPosition(unsigned int pos);
	unsigned int getPosiiton();
	
	int getCash();
	void setCash(int number);
	void minusCash(int number);
	void plusCash(int number);

	int getDeposit();
	void setDeposit(int number);

	vector<struct stockData> getOwnStock();
	void buyStock(struct stockData buy);
	void sellStock(int sell,int newValue);

	vector<House&> getOwnHouse();
	void setOwnHouse(House&);
	void freeHouse(House &free);
	void buyHouse(House &buy);
	void sellHouse(House &sell);

};