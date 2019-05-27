#include <string>
#include <cstdlib>
#include <time.h>
#include "Player.h"
#include "Stock.h"

Player::~Player()
{
}

Player::Player(string setName, unsigned int setPosition, int setCash)
{
	name = setName;
	currentPosition = setPosition;
	cash = setCash;
	deposit = 0;
}

// µ¥®Ø¬[¦n
void Player::printPlayer()
{
}

void Player::setPosition(unsigned int pos)
{
	currentPosition = pos;
}

unsigned int Player::getPosiiton()
{
	return currentPosition;
}



int Player::getCash()
{
	return cash;
}

void Player::setCash(int number)
{
	cash = number;
}

void Player::minusCash(int number)
{
	cash -= number;
}

void Player::plusCash(int number)
{
	cash += number;
}

int Player::getDeposit()
{
	return deposit;
}

void Player::setDeposit(int number)
{
	deposit = number;
}



vector<struct stockData> Player::getOwnStock()
{
	return vector<struct stockData>();
}

void Player::buyStock(stockData buy)
{
	ownStock.push_back(buy);
	deposit -= buy.value;
}

void Player::sellStock(int sell, int newValue)
{
	ownStock.erase(ownStock.begin() + sell);
	deposit += newValue;
}



vector<House&> Player::getOwnHouse()
{
	return ownHouse;
}

void Player::setOwnHouse(House& h)
{
	ownHouse.push_back(h);
}

void Player::freeHouse(House& free)
{
	ownHouse.push_back(free);
}

void Player::buyHouse(House& buy)
{
	cash -= buy.getPrice();
	ownHouse.push_back(buy);
}

void Player::sellHouse(House& sell)
{
	cash += sell.getPrice();
	for (int i = 0; i < ownHouse.size(); i++)
	{
		if (sell.getName() == ownHouse[i].getName())
		{
			ownHouse.erase(ownHouse.begin() + i);
			break;
		}
	}
}

void Player::stop(int i)
{
	state = 1;
	stopRound = i;
}