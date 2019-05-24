#pragma once
#include <vector>
#include "Stock.h"
#include "House.h"

using namespace std;

struct position
{
	int x;
	int y;
};

class Player
{
private:
	struct position currentPosition;
	int cash;
	int deposit;
	vector<struct stockShare> ownStock;
	vector<House> ownHouse;

public:
	Player();
	~Player();

	void printPlayer();
	
	int getCash();
	void setCash(int number);
	void minusCash(int number);
	void plusCash(int number);

	int getDeposit();
	void setDeposit(int number);

	vector<struct stockShare> getOwnStock();
	void buyStock(struct stockShare buy);
	void sellStock(int sell);

	vector<House> getOwnHouse();
	void buyHouse(House buy);
	void sellHouse(House sell);

};