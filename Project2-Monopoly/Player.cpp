#include <cstdlib>
#include <time.h>
#include "Player.h"

Player::~Player()
{
}

Player::Player()
{
	name = "Bank";
}

Player::Player(const Player &p)
{
	name = p.name;
	currentPosition = p.currentPosition;
	cash = p.cash;
	deposit = p.deposit;
	ownStock = p.ownStock;
	state = p.state;
	stopRound = p.stopRound;
    color = p.color;
}

Player::Player(string setName, unsigned int setPosition, int setCash, int setDeposit)
{
	name = setName;
	currentPosition = setPosition;
	cash = setCash;
	deposit = setDeposit;
}

void Player::operator=(Player p)
{
	name = p.name;
	currentPosition = p.currentPosition;
	cash = p.cash;
	deposit = p.deposit;
	ownStock = p.ownStock;
	state = p.state;
	stopRound = p.stopRound;
    color = p.color;
}

string Player::getName()
{
	return name;
}

void Player::setName(string n)
{
	name = n;
}

void Player::setPosition(unsigned int pos)
{
	currentPosition = pos;
}

unsigned int Player::getPosition()
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

void Player::minusDeposit(int number)
{
	deposit -= number;
}

void Player::plusDeposit(int number)
{
	deposit += number;
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

int Player::getColor()
{
	return color;
}

void Player::setColor(int co)
{
	color = co;
}



vector<House*> Player::getOwnHouse()
{
	return ownHouse;
}

void Player::setOwnHouse(House* h)
{
	ownHouse.push_back(h);
}

void Player::freeHouse(House* free)
{
	free->setOwner(this);
	ownHouse.push_back(free);
}

void Player::buyHouse(House* buy)
{
	cash -= buy->getCostOfOwn();//原本的是讀取房屋等級對應的價格getPrice()，現改成空屋的價格 by魚展
	buy->setOwner(this);//房屋要設定所有權者
	ownHouse.push_back(buy);
}

void Player::sellHouse(House* sell)
{
	/*本處的所有權變更待補 by魚展*/
	cash += sell->getPrice();//這個價格也要注意一下 by魚展
	sell->setOwner(NULL);
	for (int i = 0; i < ownHouse.size(); i++)
	{
		if (sell->getName() == ownHouse[i]->getName())
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