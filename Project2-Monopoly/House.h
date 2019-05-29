#ifndef HOUSE_H
#define HOUSE_H
#include "Block.h"

extern class Player;

class House :
    public Block
{
public:
    House(unsigned newPosition,
          string newName,
		  Player* newOwner,
		  unsigned newLevel = 0,
		  unsigned cost=0,
          vector<unsigned> newPriceList = {0,0,0,0},
          vector<unsigned> newPasserby = {}
          );

    House(House&);

    House& operator=(House);

    // 眔讽单
    unsigned getLevel();

	// 眔讽基
	unsigned getPrice();

	//眔潦禦基
	unsigned getCostOfOwn();

	//眔局Τ
	Player* getOwner();

	// 砞﹚单 sign穦繦ぇэ跑
    void setLevel(unsigned newLevel);

	//砞﹚局Τ
	void setOwner(Player*);
private:
    unsigned level;
	unsigned costOfOwn;
    vector<unsigned> tollsList;
	Player* owner;
};

#endif

